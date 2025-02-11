/**
 * \file            lib_i2c.c
 * \brief           Software i2c library
 */

/*
 * Copyright (c) 2024 Jasper
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file contrains all the software i2c functions.
 *
 * Author:          Jasper <JasperZhangSE@gmail.com>
 * Version:         v1.0.0-dev
 */

#include "lib/i2c/lib_i2c.h"
#include "FreeRTOS.h"
#include "app/config.h"
#include "lib/debug/lib_debug.h"
#include "lib/type/lib_type.h"
#include <cmsis_os.h>
#include "lib/delay/lib_delay.h"

/* Debug config */
#if I2C_DEBUG
#undef TRACE
#define TRACE(...) debug_printf(__VA_ARGS__)
#else
#undef TRACE
#define TRACE(...)
#endif /* I2C_DEBUG */
#if I2C_ASSERT
#undef ASSERT
#define ASSERT(a)                                                                                                      \
    while (!(a)) {                                                                                                     \
        debug_printf("ASSERT failed: %s %d\n", __FILE__, __LINE__);                                                    \
    }
#else
#undef ASSERT
#define ASSERT(...)
#endif /* I2C_ASSERT */

#if SORTWARE_I2C_ENABLE

static void i2c_delay(void) {
#if USE_SYS_TICK_DELAY_US
    delay_us(45);
#else
    osDelay(1);
#endif
}

status_t i2c_start(void) {
    /*    __________
     *SCL           \________
     *    ______
     *SDA       \_____________
     */
    I2C_SDA(high);
    I2C_SCL(high);
    i2c_delay();
    if (I2C_SDA_READ() == low) {
        return status_err;
    }
    I2C_SDA(low);
    i2c_delay();
    I2C_SCL(low);
    i2c_delay();
    return status_ok;
}

status_t i2c_stop(void) {
    /*          ____________
     *SCL _____/
     *               _______
     *SDA __________/
     */
    I2C_SCL(low);
    i2c_delay();
    I2C_SDA(low);
    i2c_delay();
    I2C_SCL(high);
    i2c_delay();
    I2C_SDA(high);
    i2c_delay();
    return status_ok;
}

status_t i2c_wait_ack(void)
{
    uint8_t waittime = 0;
    status_t rack = status_err;

    I2C_SDA(high);     /* 主机释放SDA线(此时外部器件可以拉低SDA线) */
    i2c_delay();
    I2C_SCL(high);     /* SCL=1, 此时从机可以返回ACK */
    i2c_delay();

    while (I2C_SDA_READ())    /* 等待应答 */
    {
        waittime++;
        if (waittime > 250)
        {
            i2c_stop();
            rack = status_ok;
            break;
        }
    }

    I2C_SCL(0);     /* SCL=0, 结束ACK检查 */
    i2c_delay();
    return rack;
}

status_t i2c_write_byte(uint8_t byte) {
    TRACE("i2c write byte = ");
    for (uint8_t i = 0; i < 8; i++) {
        if (byte & 0x80) {
            I2C_SDA(high);
        } else {
            I2C_SDA(low);
        }
        TRACE("%d ", (byte & 0x80) >> 7);
        i2c_delay();
        I2C_SCL(high);
        i2c_delay();
        I2C_SCL(low);
        i2c_delay();
        byte <<= 1;
    }
    TRACE("\r\n");

    I2C_SDA(high);
    i2c_delay();
    I2C_SCL(high);
    i2c_delay();
    if (I2C_SDA_READ() == high) {
        TRACE("i2c_write_byte error\r\n");
        return status_err;
    }
    I2C_SCL(low);
    return status_ok;
}

status_t i2c_read_byte(uint8_t* byte, uint8_t ack) {

    if (!byte) {
        return status_err;
    }

    TRACE("i2c read byte = ");

    *byte = 0;
    i2c_delay();

    for (uint8_t i = 0; i < 8; i++) {
        *byte <<= 1;
        I2C_SCL(high);
        i2c_delay();
        if (I2C_SDA_READ() == high) {
            *byte |= 0x01;
        }
        TRACE("%d ", (*byte & 0x01));

        I2C_SCL(low);
        i2c_delay();
    }
    TRACE("\n");

    if (ack) {
        I2C_SDA(high);
    } else {
        I2C_SDA(low);
    }
    i2c_delay();
    I2C_SCL(high);
    i2c_delay();
    I2C_SCL(low);
    i2c_delay();
    I2C_SDA(high);

    return status_ok;
}

status_t i2c_write_data(uint8_t device_address, uint8_t* data, uint16_t length) {

    if (!data) {
        return status_err;
    }

    if (i2c_start() != status_ok) {
        return status_err;
    }

    if (i2c_write_byte(device_address << 1 & 0xFE) != status_ok) {
        i2c_stop();
        return status_err;
    }

    for (uint16_t i = 0; i < length; i++) {
        if (i2c_write_byte(data[i]) != status_ok) {
            i2c_stop();
            return status_err;
        }
        TRACE("data[%d] = %d\r\n", i, data[i]);
    }
    TRACE("\r\n");

    i2c_stop();
    return status_ok;
}

status_t i2c_read_data(uint8_t device_address, uint8_t* data, uint16_t length, uint8_t ack) {

    if (!data) {
        TRACE("data is NULL\r\n");
        return status_err;
    }

    if (i2c_start() != status_ok) {
        TRACE("start error\r\n");
        return status_err;
    }

    if (i2c_write_byte(device_address << 1 | 0x01) != status_ok) {
        TRACE("write address error\r\n");
        i2c_stop();
        return status_err;
    }

    for (uint16_t i = 0; i < length; i++) {
        if (i2c_read_byte(&data[i], (i < length - 1) ? ack : 1) != status_ok) {
            TRACE("i2c_read_data error\r\n");
            i2c_stop();
            return status_err;
        }
        TRACE("data[%d] = %d\r\n", i, data[i]);
    }
    TRACE("\r\n");

    i2c_stop();
    return status_ok;
}

status_t i2c_write_register(uint8_t device_address, uint8_t register_address, uint8_t* data, uint8_t length) {

    if (!data) {
        return status_err;
    }

    if (i2c_start() != status_ok) {
        return status_err;
    }

    if (i2c_write_byte(device_address << 1 & 0xFE) != status_ok) {
        i2c_stop();
        return status_err;
    }

    if (i2c_write_byte(register_address) != status_ok) {
        i2c_stop();
        return status_err;
    }

    for (uint8_t i = 0; i < length; i++) {
        if (i2c_write_byte(data[i]) != status_ok) {
            i2c_stop();
            return status_err;
        }
    }

    i2c_stop();
    return status_ok;
}

status_t i2c_read_register(uint8_t device_address, uint8_t register_address, uint8_t* data, uint8_t length) {

    if (!data) {
        return status_err;
    }

    if (i2c_start() != status_ok) {
        return status_err;
    }

    if (i2c_write_byte((device_address << 1) & 0xFE) != status_ok) {
        i2c_stop();
        return status_err;
    }

    if (i2c_write_byte(register_address) != status_ok) {
        i2c_stop();
        return status_err;
    }

    if (i2c_start() != status_ok) {
        return status_err;
    }

    if (i2c_write_byte((device_address << 1) | 0x01) != status_ok) {
        i2c_stop();
        return status_err;
    }

    for (uint8_t i = 0; i < length; i++) {
        if (i == length - 1) {

            if (i2c_read_byte(&data[i], 1) != status_ok) {
                i2c_stop();
                return status_err;
            }
        } else {

            if (i2c_read_byte(&data[i], 0) != status_ok) {
                i2c_stop();
                return status_err;
            }
        }
    }

    i2c_stop();
    return status_ok;
}

#endif

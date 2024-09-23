/**
 * \file            sys.c
 * \brief           System file
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
 * This file includes all the app functions for system.
 *
 * Author:          Jasper <jasperzhangse@gmail.com>
 * Version:         v1.0.0-dev
 */

#include "app/include.h"

/* Debug config */
#if SYS_DEBUG || 1
#undef TRACE
#define TRACE(...) debug_printf(__VA_ARGS__)
#else
#undef TRACE
#define TRACE(...)
#endif /* SYS_DEBUG */
#if SYS_ASSERT
#undef ASSERT
#define ASSERT(a)                                                                                                      \
    while (1) {                                                                                                        \
        debug_printf("ASSERT failed: %s %d\n", __FILE__, __LINE__);                                                    \
    }
#else
#undef ASSERT
#define ASSERT(...)
#endif /* SYS_ASSERT */

/* Local defines */

/* global variable */
/* 10个触控点的颜色(电容触摸屏用) */
const uint16_t POINT_COLOR_TBL[10] = {RED, GREEN, BLUE, BROWN, YELLOW, MAGENTA, CYAN, LIGHTBLUE, BRRED, GRAY};

/* Forward functions */
static void sys_task(void* parameter);
void ctp_test_task(void* para);

void load_draw_dialog(void);
void lcd_draw_bline(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t size, uint16_t color);
void ctp_test(void);

/* Functions */
status_t sys_init(void)
{

    /* lcd test without lvgl */
    // lcd_show_string(30, 50, 200, 16, 16, "STM32", RED);
    // lcd_show_string(30, 70, 200, 16, 16, "TOUCH TEST", RED);
    // lcd_show_string(30, 90, 200, 16, 16, "ATOM@ALIENTEK", RED);

    // delay_ms(1500);
    // load_draw_dialog();

    // if (tp_dev.touchtype & 0X80)
    // {
    //     xTaskCreate(ctp_test_task, "ctp_test_task", 128, NULL, tskIDLE_PRIORITY + 2, NULL);
    // }

    xTaskCreate(sys_task, "sys_task", 128, NULL, tskIDLE_PRIORITY + 2, NULL);

    return status_ok;
}

static void sys_task(void* parameter)
{
    while (1) {
        osDelay(500);
        osDelay(SYS_TASK_DELAY);
    }
}

void ctp_test_task(void* para)
{
    uint8_t t = 0;
    uint8_t i = 0;
    uint16_t lastpos[10][2]; /* 最后一次的数据 */
    uint8_t maxp = 5;

    if (lcddev.id == 0X1018) {
        maxp = 10;
    }

    while (1) {
        tp_dev.scan(0);

        for (t = 0; t < maxp; t++) {
            if ((tp_dev.sta) & (1 << t)) {
                if (tp_dev.x[t] < lcddev.width && tp_dev.y[t] < lcddev.height) /* 坐标在屏幕范围内 */
                {
                    if (lastpos[t][0] == 0XFFFF) {
                        lastpos[t][0] = tp_dev.x[t];
                        lastpos[t][1] = tp_dev.y[t];
                    }

                    lcd_draw_bline(lastpos[t][0], lastpos[t][1], tp_dev.x[t], tp_dev.y[t], 2,
                                   POINT_COLOR_TBL[t]); /* 画线 */
                    lastpos[t][0] = tp_dev.x[t];
                    lastpos[t][1] = tp_dev.y[t];

                    if (tp_dev.x[t] > (lcddev.width - 24) && tp_dev.y[t] < 20) {
                        load_draw_dialog(); /* 清除 */
                    }
                }
            } else {
                lastpos[t][0] = 0XFFFF;
            }
        }

        osDelay(5);
        i++;
    }
}

/**
 * @brief       清空屏幕并在右上角显示"RST"
 * @param       无
 * @retval      无
 */
void load_draw_dialog(void)
{
    lcd_clear(WHITE);                                                /* 清屏 */
    lcd_show_string(lcddev.width - 24, 0, 200, 16, 16, "RST", BLUE); /* 显示清屏区域 */
}

/**
 * @brief       画粗线
 * @param       x1,y1: 起点坐标
 * @param       x2,y2: 终点坐标
 * @param       size : 线条粗细程度
 * @param       color: 线的颜色
 * @retval      无
 */
void lcd_draw_bline(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t size, uint16_t color)
{
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, row, col;

    if (x1 < size || x2 < size || y1 < size || y2 < size) {
        return;
    }

    delta_x = x2 - x1; /* 计算坐标增量 */
    delta_y = y2 - y1;
    row = x1;
    col = y1;

    if (delta_x > 0) {
        incx = 1; /* 设置单步方向 */
    } else if (delta_x == 0) {
        incx = 0; /* 垂直线 */
    } else {
        incx = -1;
        delta_x = -delta_x;
    }

    if (delta_y > 0) {
        incy = 1;
    } else if (delta_y == 0) {
        incy = 0; /* 水平线 */
    } else {
        incy = -1;
        delta_y = -delta_y;
    }

    if (delta_x > delta_y) {
        distance = delta_x; /* 选取基本增量坐标轴 */
    } else {
        distance = delta_y;
    }

    for (t = 0; t <= distance + 1; t++) /* 画线输出 */
    {
        lcd_fill_circle(row, col, size, color); /* 画点 */
        xerr += delta_x;
        yerr += delta_y;

        if (xerr > distance) {
            xerr -= distance;
            row += incx;
        }

        if (yerr > distance) {
            yerr -= distance;
            col += incy;
        }
    }
}

/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



int clock_analog_clock_1_hour_value = 3;
int clock_analog_clock_1_min_value = 20;
int clock_analog_clock_1_sec_value = 50;
void setup_scr_clock(lv_ui *ui)
{
	//Write codes clock
	ui->clock = lv_obj_create(NULL);
	lv_obj_set_size(ui->clock, 240, 280);
	lv_obj_set_scrollbar_mode(ui->clock, LV_SCROLLBAR_MODE_OFF);

	//Write style for clock, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->clock, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->clock, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->clock, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes clock_analog_clock_1
	static bool clock_analog_clock_1_timer_enabled = false;
	ui->clock_analog_clock_1 = lv_analogclock_create(ui->clock);
	lv_analogclock_hide_digits(ui->clock_analog_clock_1, false);
	lv_analogclock_set_major_ticks(ui->clock_analog_clock_1, 2, 10, lv_color_hex(0x0eb43c), 10);
	lv_analogclock_set_ticks(ui->clock_analog_clock_1, 2, 5, lv_color_hex(0x7b827b));
	lv_analogclock_set_hour_needle_line(ui->clock_analog_clock_1, 2, lv_color_hex(0x00ff00), -40);
	lv_analogclock_set_min_needle_line(ui->clock_analog_clock_1, 2, lv_color_hex(0x08b2d7), -30);
	lv_analogclock_set_sec_needle_line(ui->clock_analog_clock_1, 2, lv_color_hex(0x6600FF), -10);
	lv_analogclock_set_time(ui->clock_analog_clock_1, clock_analog_clock_1_hour_value, clock_analog_clock_1_min_value,clock_analog_clock_1_sec_value);
	// create timer
	if (!clock_analog_clock_1_timer_enabled) {
		lv_timer_create(clock_analog_clock_1_timer, 1000, NULL);
		clock_analog_clock_1_timer_enabled = true;
	}
	lv_obj_set_pos(ui->clock_analog_clock_1, 22, 38);
	lv_obj_set_size(ui->clock_analog_clock_1, 200, 200);

	//Write style for clock_analog_clock_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->clock_analog_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->clock_analog_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->clock_analog_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for clock_analog_clock_1, Part: LV_PART_TICKS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->clock_analog_clock_1, lv_color_hex(0x08d7ce), LV_PART_TICKS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->clock_analog_clock_1, &lv_font_montserratMedium_12, LV_PART_TICKS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->clock_analog_clock_1, 255, LV_PART_TICKS|LV_STATE_DEFAULT);

	//Write style for clock_analog_clock_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->clock_analog_clock_1, 89, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->clock_analog_clock_1, lv_color_hex(0x4e7920), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->clock_analog_clock_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//The custom code of clock.
	

	//Update current screen layout.
	lv_obj_update_layout(ui->clock);

	//Init events for screen.
	events_init_clock(ui);
}

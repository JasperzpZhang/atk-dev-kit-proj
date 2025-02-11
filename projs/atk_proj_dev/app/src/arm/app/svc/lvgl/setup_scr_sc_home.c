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

void setup_scr_sc_home(lv_ui *ui)
{
	//Write codes sc_home
	ui->sc_home = lv_obj_create(NULL);
	lv_obj_set_size(ui->sc_home, 800, 480);
	lv_obj_set_scrollbar_mode(ui->sc_home, LV_SCROLLBAR_MODE_OFF);

	//Write style for sc_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->sc_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sc_home, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->sc_home, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes sc_home_slider_1
	ui->sc_home_slider_1 = lv_slider_create(ui->sc_home);
	lv_slider_set_range(ui->sc_home_slider_1, 0, 100);
	lv_slider_set_mode(ui->sc_home_slider_1, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->sc_home_slider_1, 50, LV_ANIM_OFF);
	lv_obj_set_pos(ui->sc_home_slider_1, 166, 390);
	lv_obj_set_size(ui->sc_home_slider_1, 462, 38);

	//Write style for sc_home_slider_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->sc_home_slider_1, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sc_home_slider_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->sc_home_slider_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->sc_home_slider_1, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->sc_home_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sc_home_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for sc_home_slider_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->sc_home_slider_1, 145, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sc_home_slider_1, lv_color_hex(0x5c2ac4), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->sc_home_slider_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->sc_home_slider_1, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for sc_home_slider_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->sc_home_slider_1, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->sc_home_slider_1, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes sc_home_sw_1
	ui->sc_home_sw_1 = lv_switch_create(ui->sc_home);
	lv_obj_set_pos(ui->sc_home_sw_1, 590, 63);
	lv_obj_set_size(ui->sc_home_sw_1, 120, 50);
    
	//Write style for sc_home_sw_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->sc_home_sw_1, 149, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sc_home_sw_1, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->sc_home_sw_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sc_home_sw_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->sc_home_sw_1, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sc_home_sw_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for sc_home_sw_1, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
	lv_obj_set_style_bg_opa(ui->sc_home_sw_1, 191, LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_bg_color(ui->sc_home_sw_1, lv_color_hex(0x348a2c), LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_bg_grad_dir(ui->sc_home_sw_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_border_width(ui->sc_home_sw_1, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

	//Write style for sc_home_sw_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->sc_home_sw_1, 105, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sc_home_sw_1, lv_color_hex(0x00ffd2), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->sc_home_sw_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->sc_home_sw_1, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->sc_home_sw_1, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes sc_home_bar_1
	ui->sc_home_bar_1 = lv_bar_create(ui->sc_home);
	lv_obj_set_style_anim_time(ui->sc_home_bar_1, 1000, 0);
	lv_bar_set_mode(ui->sc_home_bar_1, LV_BAR_MODE_NORMAL);
	lv_bar_set_range(ui->sc_home_bar_1, 0, 100);
	lv_bar_set_value(ui->sc_home_bar_1, 50, LV_ANIM_OFF);
	lv_obj_set_pos(ui->sc_home_bar_1, 56, 48);
	lv_obj_set_size(ui->sc_home_bar_1, 413, 73);

	//Write style for sc_home_bar_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->sc_home_bar_1, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sc_home_bar_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->sc_home_bar_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->sc_home_bar_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->sc_home_bar_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for sc_home_bar_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->sc_home_bar_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->sc_home_bar_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->sc_home_bar_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->sc_home_bar_1, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//The custom code of sc_home.
	

	//Update current screen layout.
	lv_obj_update_layout(ui->sc_home);

}

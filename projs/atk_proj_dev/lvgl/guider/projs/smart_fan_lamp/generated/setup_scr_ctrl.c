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



void setup_scr_ctrl(lv_ui *ui)
{
	//Write codes ctrl
	ui->ctrl = lv_obj_create(NULL);
	lv_obj_set_size(ui->ctrl, 240, 280);
	lv_obj_set_scrollbar_mode(ui->ctrl, LV_SCROLLBAR_MODE_OFF);

	//Write style for ctrl, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->ctrl, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->ctrl, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->ctrl, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes ctrl_slider_light
	ui->ctrl_slider_light = lv_slider_create(ui->ctrl);
	lv_slider_set_range(ui->ctrl_slider_light, 0, 100);
	lv_slider_set_mode(ui->ctrl_slider_light, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->ctrl_slider_light, 50, LV_ANIM_OFF);
	lv_obj_set_pos(ui->ctrl_slider_light, 28, 116);
	lv_obj_set_size(ui->ctrl_slider_light, 185, 19);

	//Write style for ctrl_slider_light, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->ctrl_slider_light, 74, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->ctrl_slider_light, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->ctrl_slider_light, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->ctrl_slider_light, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->ctrl_slider_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->ctrl_slider_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for ctrl_slider_light, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->ctrl_slider_light, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->ctrl_slider_light, lv_color_hex(0xb1e1fd), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->ctrl_slider_light, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->ctrl_slider_light, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for ctrl_slider_light, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->ctrl_slider_light, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->ctrl_slider_light, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes ctrl_slider_color
	ui->ctrl_slider_color = lv_slider_create(ui->ctrl);
	lv_slider_set_range(ui->ctrl_slider_color, 0, 100);
	lv_slider_set_mode(ui->ctrl_slider_color, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->ctrl_slider_color, 50, LV_ANIM_OFF);
	lv_obj_set_pos(ui->ctrl_slider_color, 28, 177);
	lv_obj_set_size(ui->ctrl_slider_color, 185, 19);

	//Write style for ctrl_slider_color, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->ctrl_slider_color, 141, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->ctrl_slider_color, lv_color_hex(0xebb28d), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->ctrl_slider_color, LV_GRAD_DIR_HOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->ctrl_slider_color, lv_color_hex(0xff6500), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(ui->ctrl_slider_color, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(ui->ctrl_slider_color, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->ctrl_slider_color, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->ctrl_slider_color, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->ctrl_slider_color, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for ctrl_slider_color, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->ctrl_slider_color, 0, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->ctrl_slider_color, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for ctrl_slider_color, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->ctrl_slider_color, 105, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->ctrl_slider_color, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->ctrl_slider_color, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->ctrl_slider_color, 9, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes ctrl_btn_1
	ui->ctrl_btn_1 = lv_btn_create(ui->ctrl);
	ui->ctrl_btn_1_label = lv_label_create(ui->ctrl_btn_1);
	lv_label_set_text(ui->ctrl_btn_1_label, "Home");
	lv_label_set_long_mode(ui->ctrl_btn_1_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->ctrl_btn_1_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->ctrl_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->ctrl_btn_1_label, LV_PCT(100));
	lv_obj_set_pos(ui->ctrl_btn_1, 28, 19);
	lv_obj_set_size(ui->ctrl_btn_1, 41, 21);

	//Write style for ctrl_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->ctrl_btn_1, 210, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->ctrl_btn_1, lv_color_hex(0x455f77), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->ctrl_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->ctrl_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->ctrl_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->ctrl_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->ctrl_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->ctrl_btn_1, &lv_font_montserratMedium_10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->ctrl_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->ctrl_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//The custom code of ctrl.
	

	//Update current screen layout.
	lv_obj_update_layout(ui->ctrl);

	//Init events for screen.
	events_init_ctrl(ui);
}

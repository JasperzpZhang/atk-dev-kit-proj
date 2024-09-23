/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


static void home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
			ui_load_scr_animation(&guider_ui, &guider_ui.ctrl, guider_ui.ctrl_del, &guider_ui.home_del, setup_scr_ctrl, LV_SCR_LOAD_ANIM_OVER_RIGHT, 200, 20, true, false);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void home_digital_clock_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.clock, guider_ui.clock_del, &guider_ui.home_del, setup_scr_clock, LV_SCR_LOAD_ANIM_NONE, 200, 20, true, false);
		break;
	}
    default:
        break;
    }
}

void events_init_home (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->home, home_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->home_digital_clock_1, home_digital_clock_1_event_handler, LV_EVENT_ALL, ui);
}

static void ctrl_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.home, guider_ui.home_del, &guider_ui.ctrl_del, setup_scr_home, LV_SCR_LOAD_ANIM_OVER_LEFT, 200, 20, true, false);
		break;
	}
    default:
        break;
    }
}

void events_init_ctrl (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->ctrl_btn_1, ctrl_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void clock_analog_clock_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.home, guider_ui.home_del, &guider_ui.clock_del, setup_scr_home, LV_SCR_LOAD_ANIM_NONE, 200, 20, true, false);
		break;
	}
    default:
        break;
    }
}

void events_init_clock (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->clock_analog_clock_1, clock_analog_clock_1_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}

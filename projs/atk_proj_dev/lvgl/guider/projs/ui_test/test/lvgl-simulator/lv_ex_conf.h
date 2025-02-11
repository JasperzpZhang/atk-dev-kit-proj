/**
 * @file lv_ex_conf.h
 *
 */

#ifndef LV_EX_CONF_H
#define LV_EX_CONF_H


/*******************
 * GENERAL SETTING
 *******************/
#define LV_EX_PRINTF       1       /*Enable printf-ing data*/
#define LV_EX_KEYBOARD     1       /*Add PC keyboard support to some examples (`lv_drivers` repository is required)*/
#define LV_EX_MOUSEWHEEL   1       /*Add 'encoder' (mouse wheel) support to some examples (`lv_drivers` repository is required)*/

/*******************
 *   TEST USAGE
 *******************/
#define LV_USE_TESTS       1

/*******************
 * TUTORIAL USAGE
 *******************/
#define LV_USE_TUTORIALS   1

/*********************
 * APPLICATION USAGE
 *********************/

/* Test the graphical performance of your MCU
 * with different settings*/
#define LV_USE_BENCHMARK   1

/*A demo application with Keyboard, Text area, List and Chart
 * placed on Tab view */
#define LV_USE_DEMO        1
#if LV_USE_DEMO
#define LV_DEMO_WALLPAPER  1    /*Create a wallpaper too*/
#define LV_DEMO_SLIDE_SHOW 0    /*Automatically switch between tabs*/
#endif

/*MCU and memory usage monitoring*/
#define LV_USE_SYSMON      1

/*A terminal to display received characters*/
#define LV_USE_TERMINAL    1

/*Touch pad calibration with 4 points*/
#define LV_USE_TPCAL       1

#endif /*LV_EX_CONF_H*/


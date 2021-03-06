#ifndef _LVGL_GUI_H_
#define _LVGL_GUI_H_

#include "lvgl.h"

extern unsigned char srceen;

LV_FONT_DECLARE(ziyuanyuanti_16);
LV_FONT_DECLARE(ziyuanyuanti_24);
LV_FONT_DECLARE(yumo_16);
LV_IMG_DECLARE(logo_80);
LV_IMG_DECLARE(logo_name_30);
LV_IMG_DECLARE(login_phone_150);
LV_IMG_DECLARE(sw_off);
LV_IMG_DECLARE(sw_on);
LV_IMG_DECLARE(V_30);
LV_IMG_DECLARE(A_30);
LV_IMG_DECLARE(W_30);
LV_IMG_DECLARE(headimg_46);

extern uint8_t headimg_46_map[4232];

typedef struct
{
    lv_obj_t *all_label_notice;   
    lv_obj_t *login_screen;
    lv_obj_t *login_qr;
    lv_obj_t *login_btn;
    lv_obj_t *login_btn_label;
    lv_obj_t *login_btn2;
    lv_obj_t *login_img1;
    lv_obj_t *login_img2;
    lv_obj_t *login_img3;
    lv_obj_t *reservation_screen;
    lv_obj_t *reservation_img1;
    lv_obj_t *reservation_img2;
    lv_obj_t *reservation_label1;
    lv_obj_t *reservation_label2;
    lv_obj_t *reservation_img_head;
    lv_obj_t *reservation_label_name;
    lv_obj_t *reservation_label_ID;
    lv_obj_t *user_screen;
    lv_obj_t *user_tabview;
    lv_obj_t *user_tabview_tab1;
    lv_obj_t *user_tabview_tab1_imgbtn;
    lv_obj_t *user_tabview_tab2;
    lv_obj_t *user_tabview_tab2_chart_volt;
    lv_chart_series_t *user_tabview_tab2_chart_series_volt;
    lv_obj_t *user_tabview_tab2_img_volt;
    lv_obj_t *user_tabview_tab2_label_volt;
    lv_obj_t *user_tabview_tab2_label_volt_num;
    lv_obj_t *user_tabview_tab2_chart_curr;
    lv_chart_series_t *user_tabview_tab2_chart_series_curr;
    lv_obj_t *user_tabview_tab2_img_curr;
    lv_obj_t *user_tabview_tab2_label_curr;
    lv_obj_t *user_tabview_tab2_label_curr_num;
    lv_obj_t *user_tabview_tab2_chart_power;
    lv_chart_series_t *user_tabview_tab2_chart_series_power;
    lv_obj_t *user_tabview_tab2_img_power;
    lv_obj_t *user_tabview_tab2_label_power;
    lv_obj_t *user_tabview_tab2_label_power_num;
    lv_obj_t *user_tabview_tab3;
    lv_obj_t *user_tabview_tab3_img_head;
    lv_obj_t *user_tabview_tab3_label_username;
    lv_obj_t *user_tabview_tab3_label_username_value;
    lv_obj_t *user_tabview_tab3_label_ID;
    lv_obj_t *user_tabview_tab3_label_ID_value;
}lvgl_gui_t;

lvgl_gui_t *lvgl_gui;


void login_srceen_events_init();
void user_screen_events_init();

void lvgl_init();
void lvgl_gui_login_screen();
void lvgl_gui_reservation_screen();
void lvgl_gui_user_screen();
void lvgl_gui_start();

void init_img46();

#endif // _LVGL_GUI_H_

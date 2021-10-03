#include <stdio.h>
#include <string.h>
#include "driver/gpio.h"
#include "lvgl.h"
#include "wifi.h"
#include "uart.h"
#include "http.h"
#include "gpio.h"
#include "server_receive_transmit.h"
#include "hlw8032.h"
#include "lvgl_gui.h"
#include "event.h"

TaskHandle_t Device_Event_Handle;

char label_volt_str[10];
char label_curr_str[10];
char label_power_str[10];

void Device_main_task()
{
    static int free_bit = 1;
    static int reservation_bit = 0;
    static int using_bit = 0;
    while(1)
    {
        if(strcmp(http_rec.state_state , "0") == 0)             //无用户使用
        {
            printf("Device State Code 0\r\n");
            using_bit = 0;
            reservation_bit = 0;
            if(free_bit == 0)
            {
                lv_obj_clean(lv_scr_act());
                lvgl_gui_login_screen();
                vTaskDelay(200 / portTICK_PERIOD_MS);
                lv_scr_load(lvgl_gui->login_screen);
                relay_off();
                free_bit = 1;
            }
        }
        else if(strcmp(http_rec.state_state , "1") == 0)        //已经被预约
        {
            printf("Device State Code 1\r\n");
            using_bit = 0;
            free_bit = 0;
            if(reservation_bit == 0)
            {
                lv_obj_clean(lv_scr_act());
                lvgl_gui_reservation_screen();
                vTaskDelay(200 / portTICK_PERIOD_MS);
                lv_scr_load(lvgl_gui->reservation_screen);
                relay_off();
                reservation_bit = 1;
            }

        }
        else if(strcmp(http_rec.state_state , "2") == 0)        //用户正在使用
        {
            printf("Device State Code 2\r\n");
            free_bit = 0;
            reservation_bit = 0;
            if(using_bit == 0)
            {
                lv_obj_clean(lv_scr_act());
                lvgl_gui_user_screen();
                vTaskDelay(200 / portTICK_PERIOD_MS);
                lv_scr_load(lvgl_gui->user_screen);
                using_bit = 1;
            }

            sprintf(label_volt_str , "%.2fV" , hlw8032_rec->voltage);
            sprintf(label_curr_str , "%.2fA" , hlw8032_rec->current);
            sprintf(label_power_str , "%.1fW" , hlw8032_rec->power);
            lv_label_set_text(lvgl_gui->user_tabview_tab2_label_volt_num , label_volt_str);
            lv_label_set_text(lvgl_gui->user_tabview_tab2_label_curr_num , label_curr_str);
            lv_label_set_text(lvgl_gui->user_tabview_tab2_label_power_num , label_power_str);

            lv_chart_set_next(lvgl_gui->user_tabview_tab2_chart_volt , lvgl_gui->user_tabview_tab2_chart_series_volt , hlw8032_rec->voltage);
            lv_chart_set_next(lvgl_gui->user_tabview_tab2_chart_curr , lvgl_gui->user_tabview_tab2_chart_series_curr , hlw8032_rec->current);
            lv_chart_set_next(lvgl_gui->user_tabview_tab2_chart_power , lvgl_gui->user_tabview_tab2_chart_series_power , hlw8032_rec->power);
            vTaskDelay(2000 / portTICK_PERIOD_MS);

        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}



void Device_Event_init()
{
    xTaskCreate(Device_main_task, 
                "Device_main", 
                4096 * 3, 
                NULL, 
                7, 
                &Device_Event_Handle);
}

void Device_Event_uninit()
{
    vTaskDelete(Device_Event_Handle);
}


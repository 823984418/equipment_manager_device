#include <stdio.h>
#include <string.h>
#include <time.h>
#include "lvgl.h"
#include "wifi.h"
#include "uart.h"
#include "http.h"
#include "gpio.h"
#include "key.h"
#include "server_receive_transmit.h"
#include "hlw8032.h"
#include "lvgl_gui.h"



void app_main(void)
{
    gpio_init();
    key_init();
    hlw8032_init();
    wifi_init();
    lvgl_init();

    // while(1)
    // {
    //     if(srceen == 1)
    //     {
    //         // sprintf(label_volt_str , "%.2fV" , hlw8032_rec->voltage);
    //         // sprintf(label_curr_str , "%.2fA" , hlw8032_rec->current);
    //         // sprintf(label_power_str , "%.1fW" , hlw8032_rec->power);
    //         // lv_label_set_text(lvgl_gui->user_tabview_tab2_label_volt_num , label_volt_str);
    //         // lv_label_set_text(lvgl_gui->user_tabview_tab2_label_curr_num , label_curr_str);
    //         // lv_label_set_text(lvgl_gui->user_tabview_tab2_label_power_num , label_power_str);

    //         // lv_chart_set_next(lvgl_gui->user_tabview_tab2_chart_volt , lvgl_gui->user_tabview_tab2_chart_series_volt , hlw8032_rec->voltage);
    //         // lv_chart_set_next(lvgl_gui->user_tabview_tab2_chart_curr , lvgl_gui->user_tabview_tab2_chart_series_curr , hlw8032_rec->current);
    //         // lv_chart_set_next(lvgl_gui->user_tabview_tab2_chart_power , lvgl_gui->user_tabview_tab2_chart_series_power , hlw8032_rec->power);
    //         // vTaskDelay(2000 / portTICK_PERIOD_MS);
    //     }
    // }

    time_t ntp_time;

    while(1)
    {
        time(&ntp_time);
        //printf("time = %s", ctime(&ntp_time));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

}

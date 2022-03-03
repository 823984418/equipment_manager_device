#include <stdio.h>
#include <string.h>
#include <time.h>

#include "esp_wifi.h"

#include "lvgl.h"
#include "wifi.h"
#include "uart.h"
#include "http.h"
#include "gpio.h"
#include "key.h"
#include "event.h"

#include "server_receive_transmit.h"
#include "im1281b.h"
//#include "hlw8032.h"
#include "lvgl_gui.h"



void app_main(void)
{
    // uint8_t mac[6] = {0x12, 0x34, 0x56, 0x78, 0x90};
    // esp_base_mac_addr_set(mac);
    
    gpio_init();
    key_init();
    //hlw8032_init();
    im1281b_init();
    lvgl_init();
    wifi_init();
    //Device_Event_init();

    // while(1)
    // {
    //     if(srceen == 1)
    //     {
    //         sprintf(label_volt_str , "%.2fV" , im1281b_data->voltage);
    //         sprintf(label_curr_str , "%.2fA" , im1281b_data->current);
    //         sprintf(label_power_str , "%.1fW" , im1281b_data->power);
    //         lv_label_set_text(lvgl_gui->user_tabview_tab2_label_volt_num , label_volt_str);
    //         lv_label_set_text(lvgl_gui->user_tabview_tab2_label_curr_num , label_curr_str);
    //         lv_label_set_text(lvgl_gui->user_tabview_tab2_label_power_num , label_power_str);

    //         lv_chart_set_next(lvgl_gui->user_tabview_tab2_chart_volt , lvgl_gui->user_tabview_tab2_chart_series_volt , im1281b_data->voltage);
    //         lv_chart_set_next(lvgl_gui->user_tabview_tab2_chart_curr , lvgl_gui->user_tabview_tab2_chart_series_curr , im1281b_data->current);
    //         lv_chart_set_next(lvgl_gui->user_tabview_tab2_chart_power , lvgl_gui->user_tabview_tab2_chart_series_power , im1281b_data->power);
    //         vTaskDelay(2000 / portTICK_PERIOD_MS);
    //     }
    // }

    time_t ntp_time;

//    while(1)
//    {
        time(&ntp_time);
        //printf("time = %s", ctime(&ntp_time));
        //vTaskDelay(1000 / portTICK_PERIOD_MS);
//    }

}

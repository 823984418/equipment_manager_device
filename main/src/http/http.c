#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"
#include "esp_log.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"

#include "gpio.h"
#include "http.h"
#include "server_receive_transmit.h"
#include "hlw8032.h"
#include "event.h"

/*
===========================
宏定义
=========================== 
*/
#define false		0
#define true		1
#define errno		(*__errno())

//http组包宏，获取http接口参数
#define WEB_SERVER          "ztuser.ltd"              
#define WEB_PORT            "80"
#define WEB_URL             "/equipment_server/device1/link?"
#define WEB_uuid            "1"
#define WEB_password        "0"

server_receive_data_t http_rec = {0};

TaskHandle_t HTTP_Handle;

//http请求包
//static char *REQUEST;
static char REQUEST[1024];
/* = "GET "WEB_URL""APIKEY"&location="city"&language="language" HTTP/1.1\r\n"
    "Host: "WEB_SERVER"\r\n"
    "\r\n"; */


static const char *HTTP_TAG = "http_task";

void http_create_request()
{
    //sprintf(REQUEST , "GET ""/v3/weather/now.json?key=""g3egns3yk2ahzb0p""&location=""suzhou""&language=""en"" HTTP/1.1\r\n""Host: ""api.thinkpage.cn""Connection: close\r\n""");
    sprintf(REQUEST , "GET "WEB_URL"uuid="WEB_uuid"&password="WEB_password"&relay=%d&vlotage=%.2f&current=%.2f&power=%.2f&electricity=%.2f HTTP/1.1\r\n""Host: "WEB_SERVER"\r\n""\r\n" , relay_state , hlw8032_rec->voltage , hlw8032_rec->current , hlw8032_rec->power , hlw8032_rec->power);
    //sprintf(REQUEST , "GET ""Host: ""ztuser.ltd""\r\n""\r\n");
    printf("%s\n",REQUEST);
}

void http_get_task(void *pvParameters)
{
    const struct addrinfo hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM,
    };
    struct addrinfo *res;
    struct in_addr *addr;
    int s, r;
    char recv_buf[1024];
    char mid_buf[1024];
    int index;
    while(1) {
        
        //DNS域名解析
        int err = getaddrinfo(WEB_SERVER, WEB_PORT, &hints, &res);
        if(err != 0 || res == NULL) {
            ESP_LOGE(HTTP_TAG, "DNS lookup failed err=%d res=%p\r\n", err, res);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            continue;
        }
 
        //打印获取的IP
        addr = &((struct sockaddr_in *)res->ai_addr)->sin_addr;
        ESP_LOGI(HTTP_TAG, "DNS lookup succeeded. IP=%s\r\n", inet_ntoa(*addr));
 
        //新建socket
        s = socket(res->ai_family, res->ai_socktype, 0);
        if(s < 0) {
            ESP_LOGE(HTTP_TAG, "... Failed to allocate socket.\r\n");
            close(s);
            freeaddrinfo(res);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            continue;
        }
        //连接ip
        if(connect(s, res->ai_addr, res->ai_addrlen) != 0) {
            ESP_LOGE(HTTP_TAG, "... socket connect failed errno=%d\r\n", errno);
            close(s);
            freeaddrinfo(res);
            vTaskDelay(4000 / portTICK_PERIOD_MS);
            continue;
        }
        freeaddrinfo(res);

        http_create_request();

        //发送http包
        if (write(s, REQUEST, strlen(REQUEST)) < 0) {
            ESP_LOGE(HTTP_TAG, "... socket send failed\r\n");
            close(s);
            vTaskDelay(4000 / portTICK_PERIOD_MS);
            continue;
        }
        //清缓存
        memset(mid_buf,0,sizeof(mid_buf));
        //获取http应答包
        do {
            bzero(recv_buf, sizeof(recv_buf));
            r = read(s, recv_buf, sizeof(recv_buf)-1);
            //printf("recv_buf:%s\r\n" , recv_buf);
            strcat(mid_buf,recv_buf);
        } while(r > 0);
        //json解析
        printf("http receive IS :\n");
        printf("%s\n",mid_buf);

        http_rec = server_char_parse(mid_buf);

        //关闭socket，http是短连接
        close(s);
        //free(REQUEST);
        //延时一会
        for(int countdown = 3; countdown >= 0; countdown--) {
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
}

void http_task_init()
{
    xTaskCreate(http_get_task, 
                "http_get_task", 
                4096 * 4, 
                NULL, 
                7, 
                &HTTP_Handle);
    
}

void http_task_uninit()
{
    
    vTaskDelete(HTTP_Handle);
}

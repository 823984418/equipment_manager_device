#include <string.h>
#include <stdlib.h>
#include <stdint.h>
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

#include "Device_Info.h"
#include "gpio.h"
#include "http.h"
#include "server_receive_transmit.h"
#include "lvgl_gui.h"

#include "im1281b.h"
#include "event.h"

#include "get_user_img.h"

static const char *USER_IMG_TAG = "user_img";

static char IMG_REQUEST[1024];

// void img_data_move(uint8_t * data)
// {
//     int i;
//     for(i = 0 ; i < strlen((char *)data) ; i++)
//     {
//         data[i] = data[i + 9];
//     }
// }

char imgr[6000];

void http_get_user_img()
{
    uint32_t img_x;
    uint32_t img_y;
    
    const struct addrinfo hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM,
    };
    struct addrinfo *res;
    struct in_addr *addr;
    int s, r;
    char recv_buf[6000] = "";
    //char mid_buf[1024];
    //char imgr[10000];
    
    int index;

    //imgr = (char *)malloc(sizeof(char));
    //char * imgp;
    char * imgp;

    //while(1) {
        
        //DNS域名解析
        int err = getaddrinfo("ztuser.ltd", "80", &hints, &res);
        if(err != 0 || res == NULL) {
            ESP_LOGE(USER_IMG_TAG, "DNS lookup failed err=%d res=%p\r\n", err, res);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            return;
        }
 
        //打印获取的IP
        addr = &((struct sockaddr_in *)res->ai_addr)->sin_addr;
        ESP_LOGI(USER_IMG_TAG, "DNS lookup succeeded. IP=%s\r\n", inet_ntoa(*addr));
 
        //新建socket
        s = socket(res->ai_family, res->ai_socktype, 0);
        if(s < 0) {
            ESP_LOGE(USER_IMG_TAG, "... Failed to allocate socket.\r\n");
            close(s);
            freeaddrinfo(res);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            return;
        }
        printf("socket ok \n");
        //连接ip
        if(connect(s, res->ai_addr, res->ai_addrlen) != 0) {
            ESP_LOGE(USER_IMG_TAG, "... socket connect failed errno=%d\r\n", errno);
            close(s);
            freeaddrinfo(res);
            vTaskDelay(4000 / portTICK_PERIOD_MS);
            return;
        }
        freeaddrinfo(res);
        printf("connect ip ok \n");
        
        sprintf(IMG_REQUEST , "GET /equipment_server/deviceGetUserImage?uuid="DEV_UUID"&password="DEV_PSW" HTTP/1.1\r\nHost: ztuser.ltd\r\n\r\n");


        //发送http包
        if (write(s, IMG_REQUEST, strlen(IMG_REQUEST)) < 0) {
            ESP_LOGE(USER_IMG_TAG, "... socket send failed\r\n");
            close(s);
            vTaskDelay(4000 / portTICK_PERIOD_MS);
            return;
        }
        //清缓存
        //memset(mid_buf,0,sizeof(mid_buf));

        //printf("http send ok \n");

        //获取http应答包

            // bzero(recv_buf, sizeof(recv_buf));
            // r = read(s, recv_buf, 1);
            // if(strcmp(recv_buf , 0x00) == 0)
            // {
            //     printf("Get user img successful\n");
            //     r = read(s, recv_buf, 8);
            //     img_x = ((uint32_t)recv_buf[0]<<16) + ((uint32_t)recv_buf[1]<<8) + ((uint32_t)recv_buf[2]);
            //     img_y = ((uint32_t)recv_buf[0]<<16) + ((uint32_t)recv_buf[1]<<8) + ((uint32_t)recv_buf[2]);
            //     printf("img_x : %d , img_y : %d\n", img_x , img_y);
            // }
            // else if(strcmp(recv_buf , 0x04) == 0)
            // {
            //     printf("NO user\n");
            // }

            bzero(imgr, sizeof(imgr));
            char * pimgr = imgr;
            size_t sr =0;
        do {
            
            bzero(recv_buf, sizeof(recv_buf));
            r = read(s, imgr+sr, sizeof(imgr)-sr);
            sr +=r;
            //printf("recv_buf:\r\n");
            //strcat(imgr,recv_buf);
        } while(r > 0);
    
        // printf("img_http_rec ok\n");

        //printf("recbuf:%s\n" , imgr);

        //imgp = strstr(imgr , "\r\n\r\n");
        // //strcpy(imgr , strstr(imgr , "\r\n\r\n"));
        // printf("mm\n");
        // if(imgp[4] == 0x00)
        // {
        //     printf("0x00\n");
        //     imgp = imgp + 9 + 4;
        //     printf("11\n");
        //     strcpy((char*)headimg_46_map , imgp);
        //     printf("cpy\n");
        //     //headimg_46_map = (uint8_t*)imgp;
        // }
        //printf("recbuf:%s\n" , imgr);
        //bzero(recv_buf, sizeof(recv_buf));
        //printf("get img http ok\n");

        imgp = strstr(imgr , "\r\n\r\n");
        if(imgp != NULL)
        {
            //printf("get 2img ok\n");
            imgp = imgp + 13;
            //printf("get real 2img ok\n");
            //printf("imgbuf:%s\n" , imgp);
            //printf("print real 2img ok\n");
            memcpy(headimg_46_map , imgp , 4232);
        }

        // recv_buf = strstr(imgr , "\r\n\r\n");
        // printf("get 2img ok\n");
        // recv_buf = recv_buf + 13;
        // printf("get real 2img ok\n");
        // printf("imgbuf:%s\n" , recv_buf);
        // printf("print real 2img ok\n");
        // memcpy(headimg_46_map , recv_buf , 4232);

        // imgp = &recv_buf[9];
        // headimg_46_map = imgp;
        // if(recv_buf[4] == 0x00)
        // {
        //     printf("0x00\n");
        //     imgp = imgp + 9 + 4;
        //     printf("11\n");
        //     strcpy((char*)headimg_46_map , imgp);
        //     printf("cpy\n");
        //     //headimg_46_map = (uint8_t*)imgp;
        // }

        

        //json解析
        // printf("http receive IS :\n");
        // printf("%s\n",mid_buf);

        

        //关闭socket，http是短连接
        close(s);
        printf("close ok\n");
        //free(imgr);
        //free(REQUEST);
        //延时一会
        // for(int countdown = 3; countdown >= 0; countdown--) {
        //     vTaskDelay(1000 / portTICK_PERIOD_MS);
        // }
        printf("img ok\n");
    //}
}



void user_img_parse(char * data)
{

}
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/uart.h"
#include "uart.h"
#include "hlw8032.h"

unsigned char hlw8032_str[24];
unsigned char pf_bit=0;
unsigned char pf_count=0;
unsigned int pf_num=0;

hlw8032_data_t *hlw8032_rec;
hlw8032_data_char_t *hlw8032_rec_str;

void hlw8032_data_parse(unsigned char *rec_data)
{

    hlw8032_rec->voltage = ((float)(rec_data[2] * 65536 + rec_data[3] * 256 + rec_data[4]) / (float)(rec_data[5] * 65536 + rec_data[6] * 256 + rec_data[7])) * VOLTAGE_PARAMETER;
    hlw8032_rec->current = ((float)(rec_data[8] * 65536 + rec_data[9] * 256 + rec_data[10]) / (float)(rec_data[11] * 65536 + rec_data[12] * 256 + rec_data[13])) * CURRENT_PARAMETER;
    hlw8032_rec->power = ((float)(rec_data[14] * 65536 + rec_data[15] * 256 + rec_data[16]) / (float)(rec_data[17] * 65536 + rec_data[18] * 256 + rec_data[19])) * VOLTAGE_PARAMETER * CURRENT_PARAMETER;
    hlw8032_rec->electricity = (float)(pf_count * 65536 + (rec_data[21] * 256 + rec_data[22])) * (float)((rec_data[14] * 65536 + rec_data[15] * 256 + rec_data[16]) * VOLTAGE_PARAMETER * CURRENT_PARAMETER) / (float)(3600.0 * 1000000000.0);

    // //printf("vlot:%.2f\n",hlw8032_rec->voltage);
    // sprintf(hlw8032_rec_str->voltage_str , "%.2f" , hlw8032_rec->voltage);
    // //printf("curr:%.2f\n",hlw8032_rec->current);
    // sprintf(hlw8032_rec_str->current_str , "%.2f" , hlw8032_rec->current);
    // //printf("pow:%.2f\n",hlw8032_rec->power);
    // sprintf(hlw8032_rec_str->power_str , "%.2f" , hlw8032_rec->power);
    // //printf("ele:%.3f\n",hlw8032_rec->electricity);
    // sprintf(hlw8032_rec_str->electricity_str , "%.2f" , hlw8032_rec->power);

    vTaskDelay(1000 / portTICK_PERIOD_MS);
}

void hlw8032_data_receive()
{
    int i,j;
    unsigned int checksum=0;
    unsigned char *uart1_receive_data = (unsigned char*)malloc(UART1_BUF_SIZE + 1);


    

    /**��UART1�������ݵ����������ͣ**/
    //vTaskSuspend(uart1_task_handler);

    while(1)
    {
        int len = uart_read_bytes(UART_NUM_1 , uart1_receive_data , UART1_BUF_SIZE , 10 / portTICK_RATE_MS);
        //uart_write_bytes(UART_NUM_1, (const char *) uart1_receive_data, len);

        /**�ҵ�hlw8032�ļ��Ĵ���**/
        for(i=1 ; ((uart1_receive_data[i]!=0x5A)&&((uart1_receive_data[i]!=0x55)||(uart1_receive_data[i]!=0xF2))) ; i++);   
        /**�ҵ�hlw8032�ļ��Ĵ�����24���ֽڴ��������Ա��������**/
        for(j=0;j<24;j++)                           
        {
            hlw8032_str[j]=uart1_receive_data[i-1];
            i++;
        }

        //vTaskDelay(50 / portTICK_PERIOD_MS);

        /**�����ݽ��кϷ����ж�**/
        /**�ж�У��ͼĴ���ֵ�Ƿ�ͳ�״̬�Ĵ��������Ĵ�����У��ͼĴ���������мĴ���֮�͵ĵͰ�λ�Ƿ���ͬ**/
        checksum = 0;
        for(i=2;i<23;i++)
        {
            checksum = checksum + hlw8032_str[i];
        }
        checksum = checksum & 0x00ff;
        if(checksum==hlw8032_str[23])
        {
            if((hlw8032_str[20] & 0x80)!=pf_bit)        //�ж�pf�Ĵ����Ƿ������
            {
                pf_count++;
                pf_bit=(hlw8032_str[20] & 0x80);
            }
            //if((hlw8032_str[20] & 0x70)==0x70)              //�жϵ�ѹ���������Ƿ�������
            //{
                hlw8032_data_parse(hlw8032_str);
            //}
        }
    }
    
    /**��UART1�������ݵ�����ָ�**/
    //vTaskResume(uart1_task_handler);
}

void hlw8032_init()
{
    //����ռ�
    hlw8032_rec_str=(hlw8032_data_char_t*)malloc(sizeof(hlw8032_data_char_t));
    hlw8032_rec=(hlw8032_data_t*)malloc(sizeof(hlw8032_data_t));

    uart1_init();
    xTaskCreate(hlw8032_data_receive, "hlw8032_data_receive_task", 1024*2, NULL, 10, NULL);
    printf("hlw8032 task init finished\n");
}

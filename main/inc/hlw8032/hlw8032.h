#ifndef _HLW8032_H_
#define _HLW8032_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#define VOLTAGE_PARAMETER 1.88
#define CURRENT_PARAMETER 1.00

//extern QueueHandle_t hlw8032_data_char_Queue;

typedef struct
{
    float voltage;
    float current;
    float power;
    float electricity;
} hlw8032_data_t;

typedef struct
{
    char voltage_str[8];
    char current_str[8];
    char power_str[8];
    char electricity_str[8];
} hlw8032_data_char_t;

extern hlw8032_data_t *hlw8032_rec;
extern hlw8032_data_char_t *hlw8032_rec_str;

void hlw8032_data_parse(unsigned char *rec_data);
void hlw8032_data_receive();
void hlw8032_init();


#endif

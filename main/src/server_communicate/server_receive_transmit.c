#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"server_receive_transmit.h"
#include"cJSON.h"

//{"code":0,"id":1,"location":"422.1","type":1,"state":2,"serverTime":1612610971003,"user":"Zuoge","start":1111,"end":1234}
//{code:0,state:{uuid:1,local:"422.1",state:0,last:1632240859000,user:0,start:null,finish:null},time:1632240862967}

/**解析服务器发来的json**/
server_receive_data_t server_char_parse( char * json_char)
{   
    char state_bit[10]; 

    server_receive_data_t server_data = {0};
    char * pstr;
    cJSON * root = NULL;
    //cJSON * next = NULL;
    cJSON * item = NULL;

    char * index = strchr(json_char , '{');

    
    //strcpy(json_char , index);
    //printf("%s\n" , index);

    root = cJSON_Parse(index);

    if(!root)
    {
        printf("cJSON Error before: [%s]\n",cJSON_GetErrorPtr());
    }
    else
    {
        pstr = cJSON_PrintUnformatted(root);
        printf("cJSON is:\r\n%s\n", pstr); //无格式方式打印json
        cJSON_free(pstr);
        
        printf("ok\n");

        item = cJSON_GetObjectItem(root, "time");
        pstr = cJSON_Print(item);
        sprintf(server_data.time , "%s" , pstr);
        cJSON_free(pstr);
        
        printf("ok1\n");

        item = cJSON_GetObjectItem(root, "code");
        pstr = cJSON_Print(item);
        sprintf(server_data.code , "%s" , pstr);
        cJSON_free(pstr);

        item = cJSON_GetObjectItem(root, "state");
        pstr = cJSON_Print(item);
        sprintf(server_data.state , "%s" , pstr);
        cJSON_free(pstr);

        if(strcmp(server_data.state , "0") == 0)
        {
            item = cJSON_GetObjectItem(root, "reserved");
            pstr = cJSON_Print(item);
            sprintf(server_data.reserved , "%s" , pstr);
            cJSON_free(pstr);

            if(strcmp(server_data.reserved , "0") == 0)
            {
                sprintf(server_data.state_state , "0");  
            }
            else if(strcmp(server_data.reserved , "1") == 0)
            {
                sprintf(server_data.state_state , "1");
                item = cJSON_GetObjectItem(root, "userAccount");
                sprintf(server_data.state_uuid , "%s" , item->valuestring);
                item = cJSON_GetObjectItem(root, "userName");
                sprintf(server_data.state_user , "%s" , item->valuestring); 
            }
        }
        else if(strcmp(server_data.state , "1") == 0)
        {
            item = cJSON_GetObjectItem(root, "control");
            sprintf(server_data.control , "%s" , item->valuestring);
            item = cJSON_GetObjectItem(root, "userAccount");
            //sprintf(server_data.state_uuid , "%s" , cJSON_Print(item));
            sprintf(server_data.state_uuid , "%s" , item->valuestring);
            item = cJSON_GetObjectItem(root, "userName");
            //sprintf(server_data.state_user , "%s" , cJSON_Print(item));  
            sprintf(server_data.state_user , "%s" , item->valuestring); 
            sprintf(server_data.state_state , "2");
        }


        // /**获取每一个键值并存入对应的结构体变量**/
        // item = cJSON_GetObjectItem(root, "state");
        // sprintf(state_bit , "%s" , cJSON_Print(item));

        // if(strcmp(state_bit , "0") == 0)
        // {
        //     item = cJSON_GetObjectItem(root, "time");
        //     sprintf(server_data.time , "%s" , cJSON_Print(item));
        //     item = cJSON_GetObjectItem(root, "code");
        //     sprintf(server_data.code , "%s" , cJSON_Print(item));
        //     item = cJSON_GetObjectItem(root, "state");
        //     sprintf(server_data.state_state , "%s" , cJSON_Print(item));         
        // }
        // else if(strcmp(state_bit , "1") == 0)
        // {
        //     item = cJSON_GetObjectItem(root, "time");
        //     sprintf(server_data.time , "%s" , cJSON_Print(item));
        //     item = cJSON_GetObjectItem(root, "code");
        //     sprintf(server_data.code , "%s" , cJSON_Print(item));
        //     item = cJSON_GetObjectItem(root, "state");
        //     sprintf(server_data.state_state , "%s" , cJSON_Print(item)); 
        //     item = cJSON_GetObjectItem(root, "control");
        //     sprintf(server_data.control , "%s" , cJSON_Print(item));
        //     item = cJSON_GetObjectItem(root, "userAccount");
        //     sprintf(server_data.state_uuid , "%s" , cJSON_Print(item));
        //     item = cJSON_GetObjectItem(root, "userName");
        //     sprintf(server_data.state_user , "%s" , cJSON_Print(item));   
        // }

        // item = cJSON_GetObjectItem(root, "code");
        // sprintf(server_data.code , "%s" , cJSON_Print(item));
        // next = cJSON_GetObjectItem(root , "state");
        // item = cJSON_GetObjectItem(next , "uuid");
        // sprintf(server_data.state_uuid , "%s" , cJSON_Print(item));
        // item = cJSON_GetObjectItem(next , "local");
        // sprintf(server_data.state_local , "%s" , cJSON_Print(item));
        // item = cJSON_GetObjectItem(next , "state");
        // sprintf(server_data.state_state , "%s" , cJSON_Print(item));
        // item = cJSON_GetObjectItem(next , "last");
        // sprintf(server_data.state_last , "%s" , cJSON_Print(item));
        // item = cJSON_GetObjectItem(next , "user");
        // sprintf(server_data.state_user , "%s" , cJSON_Print(item));
        // item = cJSON_GetObjectItem(next , "start");
        // sprintf(server_data.state_start , "%s" , cJSON_Print(item));
        // item = cJSON_GetObjectItem(next , "finish");
        // sprintf(server_data.state_finish , "%s" , cJSON_Print(item));
        // item = cJSON_GetObjectItem(root, "time");
        // sprintf(server_data.code , "%s" , cJSON_Print(item));
    }
    if(root)
        cJSON_Delete(root);

    return server_data;
}

/**构建发送至服务器的json包**/
char *server_data_build(transmit_server_data_t transmit_data)
{
    cJSON * root =  cJSON_CreateObject();
    //cJSON * item =  cJSON_CreateObject();
    //cJSON * next =  cJSON_CreateObject();
    cJSON_AddItemToObject(root, "deviceID", cJSON_CreateString(transmit_data.deviceID));
    cJSON_AddItemToObject(root, "state", cJSON_CreateNumber(transmit_data.state));
    cJSON_AddItemToObject(root, "user", cJSON_CreateString(transmit_data.user));
    cJSON_AddItemToObject(root, "voltage", cJSON_CreateNumber(transmit_data.voltage));
    cJSON_AddItemToObject(root, "current", cJSON_CreateNumber(transmit_data.current));
    cJSON_AddItemToObject(root, "power", cJSON_CreateNumber(transmit_data.power));
    cJSON_AddItemToObject(root, "electricity", cJSON_CreateNumber(transmit_data.electricity));
    return cJSON_Print(root);
}

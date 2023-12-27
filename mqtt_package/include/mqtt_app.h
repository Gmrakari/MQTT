/*
 * Date:20 April 2023 9:07 PM
 * Filename:mqtt_app.h
*/

#ifndef MQTT_APP_H
#define MQTT_APP_H

#include "../../third_party/paho_mqtt_c/include/MQTTClient.h"
#include "../../third_party/cJSON/include/cJSON.h"
#include "mqtt_utils.h"


#define MQTT_BUFFLIST_SIZE  (10)
#define NUM_THREADS         (2)
#define QOS                 (0)
#define TIMEOUT             (1000L)

int _mqtt_init();
int _mqtt_deinit();

typedef void(*mqtt_cb_t)(int flag, char *buff, size_t len);

// typedef struct {
//     void *client;
//     const char *topic;
//     const unsigned char *payload;
//     size_t length;
//     unsigned char qos;
// } mqtt_client_info_t;

// typedef struct {
//     MQTTClient client;
//     char *topic;
//     MQTTClient_connectOptions mq_conn_opts;
// } mqtt_info_t;

typedef struct {
    unsigned char used;         // 0,未使用；1，已使用；2，已使用，可以释放内存
    unsigned long int timestamp;
    char *buff;
    size_t len;
    unsigned long int start_ms; // 开始计时时间ms
} mqtt_buff_t;

typedef struct {
    unsigned char used;         // 0,未使用；1，已使用；
    unsigned long int timestamp;
    unsigned long int start_ms; // 开始计时时间ms
    unsigned long int timeout;  // 超时时间ms
    mqtt_cb_t cb;
} mqtt_recv_cb_t;

typedef struct {
    MQTTClient client;
    MQTTClient_connectOptions conn_opts;
} mqtt_client_info_t;

int mqtt_app_init();

int mqtt_app_deinit();

int mqtt_app_get_conn_status(MQTTClient handle, MQTTClient_connectOptions opts);

int mqtt_app_client_publish(mqtt_client_info_t *info);

void mqtt_app_start(void);

#endif // MQTT_APP_H

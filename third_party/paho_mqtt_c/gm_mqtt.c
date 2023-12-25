
#include "gm_mqtt.h"
#include <stdio.h>
#include <pthread.h>

struct {
    mqtt_queuelist_buff_t send_list[MQTT_QUEUELIST_SIZE];
    mqtt_queuelist_buff_t recv_list[MQTT_QUEUELIST_SIZE];
    pthread_mutex_t mutex;
} private;



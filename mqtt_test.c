/*
 * Date:20 April 2023 9:02 PM
 * Filename:mqtt_test.c
*/
#include "mqtt_test.h"
#include <stdio.h>
#include <string.h>

#define QOS 0
#define TIMEOUT 1000L

volatile MQTTClient_deliveryToken deliveredtoken;

#define MQTT_SUB_TOPIC_LEN (24)
#define MQTT_PUB_TOPIC_LEN (24)
#define MQTT_CLIENT_ID_LEN (24)

typedef struct {
    MQTTClient mq_client;
    char sub_topic[MQTT_SUB_TOPIC_LEN];
    char pub_topic[MQTT_PUB_TOPIC_LEN];
    char client_id[MQTT_CLIENT_ID_LEN];
} mqtt_conn_param_t;

static mqtt_conn_param_t s_mqtt_conn_param = {0};

void delivered(void * context, MQTTClient_deliveryToken dt)
{
    printf("[%s][%d]\r\n", __func__, __LINE__);
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

static void conn_lost(void *context, char *cause)
{
    printf("cause: %s\r\n", cause);
}

static int msg_arrived(void *context, char *topic, int topic_len, MQTTClient_message *msg)
{
    printf("mqtt start\nclient_id:%s\r\n", s_mqtt_conn_param.client_id);
    char *data = msg->payload;
    printf("get data:%s\r\n", data);

    MQTTClient_freeMessage(&msg);
    MQTTClient_free(topic);
    printf("mqtt start\nclient_id:%s\r\n", s_mqtt_conn_param.client_id);
}

static void test_mqtt_pub(void)
{
    printf("[%s][%d]\r\n", __func__, __LINE__);
    char *data = "test_mqtt_pub";
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    pubmsg.payload    = data;
    pubmsg.payloadlen = (int)strlen(data);
    pubmsg.qos        = QOS;
    pubmsg.retained   = 0;
    int ret;
    if((ret = MQTTClient_publishMessage(s_mqtt_conn_param.mq_client, s_mqtt_conn_param.pub_topic, &pubmsg, &token)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to publish message, return code %d\n", ret);
    }
    printf("[%s][%d]\r\n", __func__, __LINE__);
    MQTTClient_waitForCompletion(s_mqtt_conn_param.mq_client, token, TIMEOUT);
    return;
}

int _mqtt_init(void)
{
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int ret = 0;
    printf("[%s][%d]\r\n", __func__, __LINE__);

    char address[] = "ws://broker.emqx.io:8083";

    strncpy(s_mqtt_conn_param.sub_topic, "sub_test", sizeof(s_mqtt_conn_param.sub_topic));
    strncpy(s_mqtt_conn_param.pub_topic, "pc_topic", sizeof(s_mqtt_conn_param.pub_topic));
    strncpy(s_mqtt_conn_param.client_id, "send_client_1", sizeof(s_mqtt_conn_param.client_id));

    printf("mqtt start\nclient_id:%s\r\n", s_mqtt_conn_param.client_id);

    conn_opts.username = "test";
    conn_opts.password = "test";
    printf("[%s][%d]\r\n", __func__, __LINE__);

    if((ret = MQTTClient_create(&s_mqtt_conn_param.mq_client, address, s_mqtt_conn_param.client_id, MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to create client, return code %d\n", ret);
        ret = -1;
        goto exit;
    }
    printf("[%s][%d]\r\n", __func__, __LINE__);

    if((ret = MQTTClient_setCallbacks(s_mqtt_conn_param.mq_client, NULL, conn_lost, msg_arrived, delivered)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to set callbacks, return code %d\n", ret);
        ret = -1;
        MQTTClient_destroy(&s_mqtt_conn_param.mq_client);
    }

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession      = 1;
    printf("[%s][%d]\r\n", __func__, __LINE__);

    if((ret = MQTTClient_connect(s_mqtt_conn_param.mq_client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to connect, return code %d\n", ret);
        ret = -1;
        MQTTClient_destroy(&s_mqtt_conn_param.mq_client);
    }
    printf("[%s][%d]\r\n", __func__, __LINE__);

    printf("subtopic:%s\n", s_mqtt_conn_param.sub_topic);
    if((ret = MQTTClient_subscribe(s_mqtt_conn_param.mq_client, s_mqtt_conn_param.sub_topic, QOS)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to subscribe, return code %d\n", ret);
        ret = -1;
    }

    printf("mqtt init OK\r\n");
    test_mqtt_pub();

    exit:
    return ret;
}

int _mqtt_deinit(void)
{
    printf("[%s][%d]\r\n", __func__, __LINE__);
    int ret = 0;
    if((ret = MQTTClient_unsubscribe(s_mqtt_conn_param.mq_client, s_mqtt_conn_param.sub_topic)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to unsubscribe, return code %d\n", ret);
        ret = -1;
    }

    if((ret = MQTTClient_disconnect(s_mqtt_conn_param.mq_client, 10000)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to disconnect, return code %d\n", ret);
        ret = -1;
    }
    MQTTClient_destroy(&s_mqtt_conn_param.mq_client);
    printf("[%s][%d]\r\n", __func__, __LINE__);
    return ret;
}

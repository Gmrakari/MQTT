
#ifndef _GM_MQTT_H
#define _GM_MQTT_H


#include <stdio.h>
#include <stdint.h>

#define MQTT_QUEUELIST_SIZE		(10)
#define MQTT_SEND_QOS           (2)
#define MQTT_RECV_QOS           (2)
#define MQTT_RECV_SEND_TIMEOUT	(10000)	/*10s*/

// 枚举指示MQTT状态
// 状态有：空闲、接收中、处理数据中
typedef enum {
    MQTT_STATE_IDLE = 0,
    MQTT_STATE_RECVING,
    MQTT_STATE_PROCESSING
} mqtt_recv_status_t;

typedef void (*mqtt_cb_t)(uint8_t flag, byte_info_t *byte_info); // flag:0 无效；flag : 1 有效

typedef struct {
    uint8_t *data;
    size_t len;
} byte_info_t;

typedef struct {
    uint8_t id;
    uint32_t iv;
    byte_info_t key;
    byte_info_t value;
} mqtt_prop_t;

typedef struct {
    byte_info_t user;
    byte_info_t passwd;
    byte_info_t client_id;
    byte_info_t topic;
    byte_info_t message;
    uint8_t qos;
    uint8_t version;
    uint16_t keepalive;
    mqtt_prop_t *mqtt_prop;
    size_t num_will_props;
} mqtt_opts_t;

typedef struct {
    byte_info_t topic;
    byte_info_t data;
    byte_info_t dgram;
    uint16_t id;
    uint8_t cmd;
    uint8_t qos;
    uint8_t ack;
    size_t props_start;
    size_t props_size;
} mqtt_message_t;

typedef struct {
    uint8_t used; // 0:未使用; 1:已经使用
    uint16_t timestamp;
    mqtt_cb_t cb;
    uint64_t start_ms;
    uint64_t timeout;
} mqtt_recv_cb_t;

typedef struct {
    uint8_t used; // 0:未使用; 1:已经使用; 2: 使用完可以释放内存
    uint16_t timestamp;
    byte_info_t *byte_info;
    uint64_t start_ms;
} mqtt_queuelist_buff_t;

#endif // _GM_MQTT_H

/*
 * Date:20 April 2023 9:07 PM
 * Filename:mqtt.h
*/

#ifndef __MQTT_H
#define __MQTT_H

#include "third_party/paho_mqtt_c/include/MQTTClient.h"

int _mqtt_init();
int _mqtt_deinit();

#endif //__MQTT_H

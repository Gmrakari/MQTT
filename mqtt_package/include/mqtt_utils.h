#ifndef MQTT_UTILS_H
#define MQTT_UTILS_H

#include <stdio.h>

#include <error.h>   // strerror
#include <errno.h>   // strerror
#include <string.h>  // strerror

#define USE_DEBUG  1

#if USE_DEBUG
#define LOG_DEBUG(format, ...) printf("DEBUG [%s][%d]"format"\r\n", __func__, __LINE__, ##__VA_ARGS__)

#define LOG_ERROR(format, ...) printf("ERROR [%s][%d]"format"\r\n", __func__, __LINE__, ##__VA_ARGS__)
#endif

typedef enum {
    DEBUG = 0,
    ERROR,
} LOG_TYPE_T;

#endif // MQTT_UTILS_H
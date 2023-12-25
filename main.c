#include <stdio.h>
#include "./third_party/paho_mqtt_c/mqtt.h"

int main() {
    printf("Hello, World!\n");
    _mqtt_init();
    _mqtt_deinit();
    return 0;
}

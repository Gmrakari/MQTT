#include <stdio.h>
#include "../mqtt_package/include/mqtt_app.h"

int main() {
    printf("Hello, World!\n");

    // _mqtt_init();
    // _mqtt_deinit();
    mqtt_app_init();
    mqtt_app_deinit();
    return 0;
}

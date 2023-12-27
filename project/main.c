#include <stdio.h>
#include "../mqtt_package/include/mqtt_app.h"

int main() {LOG_DEBUG();
    mqtt_app_start();LOG_DEBUG();
    return 0;
}

#include <stdio.h>
#include "../mqtt_package/include/mqtt_test.h"

int main() {
    printf("Hello, World!\n");
    _mqtt_init();
    _mqtt_deinit();
    return 0;
}

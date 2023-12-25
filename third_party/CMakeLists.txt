
list(APPEND ADD_INCLUDE "paho_mqtt_c/include")

list(APPEND ADD_DYNAMIC_LIB "libpaho-mqtt3a.so"
                            "libpaho-mqtt3a.so.1"
                            "libpaho-mqtt3a.so.1.3.11"
                            "libpaho-mqtt3c.so"
                            "libpaho-mqtt3c.so.1"
                            "libpaho-mqtt3c.so.1.3.11")

list(APPEND ADD_DEFINITIONS -fPIC)

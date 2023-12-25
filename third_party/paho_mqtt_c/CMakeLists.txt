# Set include directories
include_directories(${THIRD_PARTY_DIR}/paho_mqtt_c/include)

# Set library paths
link_directories(${THIRD_PARTY_DIR}/paho_mqtt_c/lib)

# Add third-party libraries
list(APPEND ADD_DYNAMIC_LIB "libpaho-mqtt3a.so"
                            "libpaho-mqtt3a.so.1"
                            "libpaho-mqtt3a.so.1.3.11"
                            "libpaho-mqtt3c.so"
                            "libpaho-mqtt3c.so.1"
                            "libpaho-mqtt3c.so.1.3.11")

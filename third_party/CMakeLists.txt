# third_patty/CMakeLists.txt

# cJSON
add_library(cJSON STATIC 
  cJSON/src/cJSON.c
)  

target_include_directories(cJSON
  PUBLIC cJSON/include
)

# paho-mqtt3c
add_library(paho-mqtt3c SHARED IMPORTED GLOBAL)
set_target_properties(paho-mqtt3c PROPERTIES
    IMPORTED_LOCATION
      ${CMAKE_CURRENT_SOURCE_DIR}/paho_mqtt_c/lib/libpaho-mqtt3c.so
)

target_include_directories(paho-mqtt3c
    INTERFACE paho_mqtt_c/include
)
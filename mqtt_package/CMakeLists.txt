cmake_minimum_required(VERSION 3.10)

project(mqtt_package VERSION 1.0)

set(CMAKE_C_STANDARD 99)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_library(mqtt_package ${SOURCES})

target_link_directories(mqtt_package PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/paho_mqtt_c/lib)

list(APPEND ADD_DYNAMIC_LIB "libpaho-mqtt3a.so"
                            "libpaho-mqtt3c.so")

target_link_libraries(mqtt_package PRIVATE ${ADD_DYNAMIC_LIB})

target_compile_options(mqtt_package PRIVATE -Wall -Wextra -pedantic)

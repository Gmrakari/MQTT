cmake_minimum_required(VERSION 3.10)

# Set project name and version
project(project VERSION 1.0)

# Set C standard
set(CMAKE_C_STANDARD 99)

# Set output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../mqtt_package ${CMAKE_BINARY_DIR}/mqtt_package_build)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third_party/paho_mqtt_c/lib)

list(APPEND ADD_DYNAMIC_LIB "paho-mqtt3a"
                            "paho-mqtt3c")
add_executable(app ${SOURCES})

target_link_libraries(app PRIVATE mqtt_package)

target_compile_options(app PRIVATE -Wall -Wextra -pedantic)

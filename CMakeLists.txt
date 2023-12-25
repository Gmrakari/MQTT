cmake_minimum_required(VERSION 3.10)

# Set project name and version
project(mqtt VERSION 1.0)

# Set C standard
set(CMAKE_C_STANDARD 99)

# Set output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set include directories
include_directories (mqtt PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/paho_mqtt_c/include
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

# Set source files
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
                  "${CMAKE_CURRENT_SOURCE_DIR}/third_party/paho_mqtt_c/*.c")

# Add third-party libraries
add_subdirectory(third_party/paho_mqtt_c)

# Create executable
add_executable(app ${SOURCES})

# Link libraries
target_link_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/paho_mqtt_c/lib)
target_link_libraries(app PRIVATE paho-mqtt3a paho-mqtt3c)

# Add compile options
target_compile_options(app PRIVATE -Wall -Wextra -pedantic)

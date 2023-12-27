# project/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(project_name LANGUAGES C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(app main.c)

add_subdirectory(../mqtt_package mqtt_package-build) 
add_subdirectory(../third_party third_party-build)

# 链接需要的库
target_link_libraries(app 
  mqtt_package
  paho-mqtt3c
  cJSON
  pthread
)

# 添加包含目录
target_include_directories(app 
  PRIVATE ../mqtt_package/include
  PRIVATE ../third_party/cJSON/include  
  PRIVATE ../third_party/paho_mqtt_c/include
)
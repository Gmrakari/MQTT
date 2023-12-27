# mqtt_package/CMakeLists.txt
add_library(mqtt_package STATIC
  include/mqtt_app.h
  include/mqtt_utils.h
  src/mqtt_app.c
)
target_include_directories(mqtt_package PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include> 
)

# 设置输出的库文件名(可选)
set_target_properties(mqtt_package PROPERTIES
  OUTPUT_NAME mqtt_pkg
)

# 定义输出文件位置(可选)
set_target_properties(mqtt_package PROPERTIES 
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib 
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
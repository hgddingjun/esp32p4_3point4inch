# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)
set(EXTRA_COMPONENT_DIRS "$ENV{IDF_PATH}/tools/unit-test-app/components")
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(esp32p4_3point4inch)

#设置分区表
set(PARTITION_TABLE_CSV partitions.csv)

# 设置SPIFFS镜像生成
set(SPIFFS_IMAGE_DIR "${CMAKE_CURRENT_LIST_DIR}/spiffs_image")
set(SPIFFS_IMAGE_SIZE 0x1000000)  # 16MB，根据分区表设置

# 生成SPIFFS镜像
spiffs_create_partition_image(spiffs ${SPIFFS_IMAGE_DIR} FLASH_IN_PROJECT)

set(EXTRA_COMPONENT_DIRS components/espressif__esp_lcd_jd9365)
set(EXTRA_COMPONENT_DIRS components/espressif__libpng)
set(EXTRA_COMPONENT_DIRS components/lvgl__lvgl)

# FreeType requires these definitions to build as a library
idf_build_set_property(COMPILE_DEFINITIONS "-DFT2_BUILD_LIBRARY" APPEND)
## idf_build_set_property(COMPILE_DEFINITIONS "-DFT_CONFIG_MODULES_H=<${CMAKE_CURRENT_SOURCE_DIR}/managed_components/lvgl__lvgl/src/libs/freetype/ftmodule.h>" APPEND)
## idf_build_set_property(COMPILE_DEFINITIONS "-DFT_CONFIG_OPTIONS_H=<${CMAKE_CURRENT_SOURCE_DIR}/managed_components/lvgl__lvgl/src/libs/freetype/ftoption.h>" APPEND)
idf_build_set_property(COMPILE_DEFINITIONS "-DFT_CONFIG_MODULES_H=<${CMAKE_CURRENT_SOURCE_DIR}/components/lvgl__lvgl/src/libs/freetype/ftmodule.h>" APPEND)
idf_build_set_property(COMPILE_DEFINITIONS "-DFT_CONFIG_OPTIONS_H=<${CMAKE_CURRENT_SOURCE_DIR}/components/lvgl__lvgl/src/libs/freetype/ftoption.h>" APPEND)





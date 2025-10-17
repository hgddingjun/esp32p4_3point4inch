# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)
set(EXTRA_COMPONENT_DIRS "$ENV{IDF_PATH}/tools/unit-test-app/components")
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(esp32p4_3point4inch)

# FreeType requires these definitions to build as a library
idf_build_set_property(COMPILE_DEFINITIONS "-DFT2_BUILD_LIBRARY" APPEND)
idf_build_set_property(COMPILE_DEFINITIONS "-DFT_CONFIG_MODULES_H=<${CMAKE_CURRENT_SOURCE_DIR}/managed_components/lvgl__lvgl/src/libs/freetype/ftmodule.h>" APPEND)
idf_build_set_property(COMPILE_DEFINITIONS "-DFT_CONFIG_OPTIONS_H=<${CMAKE_CURRENT_SOURCE_DIR}/managed_components/lvgl__lvgl/src/libs/freetype/ftoption.h>" APPEND)

set(EXTRA_COMPONENT_DIRS managed_components/espressif__libpng)


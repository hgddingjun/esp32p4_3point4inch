set(LV_DEMO_DIR ../components/lvgl__lvgl/demos)
set(BSP_EXTRA_DIR ../components/bsp_extra)

file(GLOB_RECURSE LV_DEMOS_SOURCES ${LV_DEMO_DIR}/*.c)
file(GLOB_RECURSE BSP_EXTRA_SRC ${BSP_EXTRA_DIR}/src/*.c)

idf_component_register(
                    SRCS
						"esp32p4_3point4inch.cpp"
						"drivers/lcd/jd9365.cpp"
						"drivers/sdmmc/sdmmc.cpp"
						# "drivers/spiffs/spiffs.cpp"
						"${LV_DEMOS_SOURCES}"
						"${BSP_EXTRA_SRC}"

                    INCLUDE_DIRS
						"./drivers"
						"./drivers/lcd"
						"./drivers/sdmmc"
						#"./drivers/spiffs"
						"."
						"${LV_DEMO_DIR}"
						"${BSP_EXTRA_DIR}/include"
					REQUIRES fatfs esp_adc esp_timer unity sdmmc freertos driver spiffs spi_flash esp_psram espressif__esp_lcd_jd9365 chmorgan__esp-audio-player chmorgan__esp-file-iterator chmorgan__esp-libhelix-mp3
                    WHOLE_ARCHIVE)

idf_component_get_property(LVGL_LIB lvgl__lvgl COMPONENT_LIB)
target_compile_options(
    ${LVGL_LIB}
    PRIVATE
        -DLV_LVGL_H_INCLUDE_SIMPLE
        -DLV_USE_DEMO_MUSIC
)
target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++14)

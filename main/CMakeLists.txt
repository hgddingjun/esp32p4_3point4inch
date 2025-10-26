idf_component_register(
                    SRCS
						"esp32p4_3point4inch.cpp"
						"drivers/lcd/jd9365.cpp"
						"drivers/sdmmc/sdmmc.cpp"
						"drivers/spiffs/spiffs.cpp"

                    INCLUDE_DIRS
						"./drivers"
						"./drivers/lcd"
						"./drivers/sdmmc"
						"./drivers/spiffs"
						"."
					REQUIRES fatfs esp_adc esp_timer unity sdmmc freertos driver spiffs spi_flash esp_psram espressif__esp_lcd_jd9365
                    WHOLE_ARCHIVE)
target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++14)
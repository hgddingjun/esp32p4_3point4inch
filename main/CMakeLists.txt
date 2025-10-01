idf_component_register(
                    SRCS
						"esp32p4_3point4inch.cpp"
						"drivers/lcd/jd9365.cpp"
						"drivers/sdmmc/sdmmc.cpp"

                    INCLUDE_DIRS
						"./drivers"
						"./drivers/lcd"
						"./drivers/sdmmc"
						"."
					REQUIRES fatfs esp_adc esp_timer unity sdmmc spi_flash
                    WHOLE_ARCHIVE)
target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++14)
idf_component_register(
                    SRCS
						"esp32p4_3point4inch.cpp"
						"drivers/lcd/jd9365.cpp"

                    INCLUDE_DIRS
						"./drivers"
						"./drivers/lcd"
						"."
					)
target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++14)
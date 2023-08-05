idf_component_register(SRCS "ssd1306_fonts.cpp" "ssd1306.cpp" "mg90s_servo.cpp" "MPU6050.cpp"
                        INCLUDE_DIRS "."
                        REQUIRES esp_wifi esp_netif esp_http_server nvs_flash driver)

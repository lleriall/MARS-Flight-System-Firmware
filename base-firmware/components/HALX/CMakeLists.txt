idf_component_register(SRCS "mg90s_servo.cpp"
                        INCLUDE_DIRS "."
                        REQUIRES esp_wifi esp_netif esp_http_server nvs_flash driver)

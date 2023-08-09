idf_component_register(SRCS "base-firmware.cpp"
                            "../components/Comms/_broadcast.cpp"
                            "../components/HALX/mg90s_servo.cpp"
                            "../components/HALX/ssd1306.cpp"
                            "../components/HALX/fan_relay.cpp"
                            "../components/PTAM/_ptam.cpp"
                            "../components/system/validateSensors.cpp"
                            "../components/system/_state.cpp"
                            "../components/system/sys_controller.cpp"

                    INCLUDE_DIRS ".")

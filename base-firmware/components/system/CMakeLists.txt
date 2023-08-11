idf_component_register(SRCS "_state.cpp"
                            "validateSensors.cpp" 
                            "sys_controller.cpp"
                        INCLUDE_DIRS "."
                        REQUIRES PTAM HALX
                         )


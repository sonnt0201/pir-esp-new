idf_component_register(SRCS "main.c"
                            "../lib/adc.c"
                            "../lib/Timestamp.c"
                            "../lib/WifiConnect.c"
                            #"../lib/print_task.c"
                           "../lib/http.c"
                        INCLUDE_DIRS "." 
                                    "../lib"
                                    )

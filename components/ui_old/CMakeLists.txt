idf_component_register(
    SRCS "ui.c"
    INCLUDE_DIRS "include"
    REQUIRES bsp esp_lvgl_port lvgl esp_timer
)

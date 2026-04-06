idf_component_register(
    SRCS
        "bsp.c"
        "drivers/esp_lcd_jd9853/esp_lcd_jd9853.c"
        "drivers/esp_lcd_touch_axs5106/esp_lcd_touch_axs5106.c"
    INCLUDE_DIRS
        "include"
        "drivers/esp_lcd_jd9853/include"
        "drivers/esp_lcd_touch_axs5106/include"
    REQUIRES driver esp_lcd esp_lcd_touch esp_timer
)

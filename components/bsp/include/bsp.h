#pragma once

#include "esp_err.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_touch.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BOARD_LCD_HRES   172
#define BOARD_LCD_VRES   320

esp_err_t bsp_init(void);

esp_lcd_panel_handle_t bsp_get_panel(void);
esp_lcd_panel_io_handle_t bsp_get_panel_io(void);
esp_lcd_touch_handle_t bsp_get_touch(void);

#ifdef __cplusplus
}
#endif

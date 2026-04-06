#include "ui.h"

#include <stdbool.h>

#include "bsp.h"
#include "esp_log.h"
#include "esp_lvgl_port.h"
#include "lvgl.h"

static const char *TAG = "ui";
static const size_t UI_DRAW_BUFFER_LINES = 50;

static lv_display_t *s_disp = NULL;
static lv_indev_t *s_indev = NULL;
static bool s_lvgl_ready = false;

static lv_obj_t *ui_create_menu_tile(lv_obj_t *parent, int32_t col, const char *title)
{
    lv_obj_t *tile = lv_tileview_add_tile(parent, col, 0, LV_DIR_HOR);
    lv_obj_set_style_bg_color(tile, lv_color_hex(0x000000), 0);
    lv_obj_set_style_bg_opa(tile, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(tile, 0, 0);
    lv_obj_set_style_pad_all(tile, 0, 0);

    lv_obj_t *label = lv_label_create(tile);
    lv_label_set_text(label, title);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0xCFFFD5), 0);
    lv_obj_set_style_text_letter_space(label, 3, 0);
    lv_obj_center(label);

    return tile;
}

esp_err_t ui_init(void)
{
    const lvgl_port_cfg_t lvgl_cfg = ESP_LVGL_PORT_INIT_CONFIG();
    ESP_ERROR_CHECK(lvgl_port_init(&lvgl_cfg));
    s_lvgl_ready = true;

    if (bsp_get_panel() != NULL) {
        ESP_ERROR_CHECK(esp_lcd_panel_set_gap(bsp_get_panel(), 34, 0));

        const lvgl_port_display_cfg_t disp_cfg = {
            .io_handle = bsp_get_panel_io(),
            .panel_handle = bsp_get_panel(),
            .buffer_size = BOARD_LCD_HRES * UI_DRAW_BUFFER_LINES,
            .double_buffer = true,
            .trans_size = 0,
            .hres = BOARD_LCD_HRES,
            .vres = BOARD_LCD_VRES,
            .monochrome = false,
            .rotation = {
                .swap_xy = false,
                .mirror_x = false,
                .mirror_y = false,
            },
            .color_format = LV_COLOR_FORMAT_RGB565,
            .flags = {
                .buff_dma = true,
                .buff_spiram = false,
                .swap_bytes = true,
                .full_refresh = false,
                .direct_mode = false,
            },
        };

        s_disp = lvgl_port_add_disp(&disp_cfg);
        if (s_disp == NULL) {
            ESP_LOGE(TAG, "LVGL display registration failed");
            return ESP_FAIL;
        }

        if (bsp_get_touch() != NULL) {
            const lvgl_port_touch_cfg_t touch_cfg = {
                .disp = s_disp,
                .handle = bsp_get_touch(),
                .scale = {
                    .x = 1.0f,
                    .y = 1.0f,
                },
            };
            s_indev = lvgl_port_add_touch(&touch_cfg);
        }
    } else {
        ESP_LOGW(TAG, "No LCD panel handle available yet, UI will run without display output");
    }

    if (!lvgl_port_lock(0)) {
        ESP_LOGE(TAG, "LVGL lock failed");
        return ESP_FAIL;
    }

    lv_obj_t *scr = lv_screen_active();
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x000000), 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);

    lv_obj_t *tileview = lv_tileview_create(scr);
    lv_obj_remove_style_all(tileview);
    lv_obj_set_size(tileview, BOARD_LCD_HRES, BOARD_LCD_VRES);
    lv_obj_center(tileview);
    lv_obj_set_style_bg_color(tileview, lv_color_hex(0x000000), 0);
    lv_obj_set_style_bg_opa(tileview, LV_OPA_COVER, 0);
    lv_obj_set_scrollbar_mode(tileview, LV_SCROLLBAR_MODE_OFF);

    ui_create_menu_tile(tileview, 0, "MENU 1");
    ui_create_menu_tile(tileview, 1, "MENU 2");
    ui_create_menu_tile(tileview, 2, "MENU 3");

    lv_obj_t *hint = lv_label_create(scr);
    lv_label_set_text(hint, "SWIPE LEFT OR RIGHT");
    lv_obj_set_style_text_font(hint, &lv_font_montserrat_12, 0);
    lv_obj_set_style_text_color(hint, lv_color_hex(0x61D67A), 0);
    lv_obj_set_style_text_letter_space(hint, 2, 0);
    lv_obj_align(hint, LV_ALIGN_BOTTOM_MID, 0, -10);

    lvgl_port_unlock();

    ESP_LOGI(TAG, "UI initialized");
    return ESP_OK;
}

void ui_set_network_name(const char *name)
{
    (void)name;
}

void ui_set_router_enabled(bool enabled)
{
    (void)enabled;
}

void ui_set_status(const char *text)
{
    (void)text;
}

void ui_set_packets(uint32_t count)
{
    (void)count;
}

void ui_set_rssi(int rssi)
{
    (void)rssi;
}

void ui_set_touch_point(uint16_t x, uint16_t y, bool touched)
{
    (void)x;
    (void)y;
    (void)touched;
}

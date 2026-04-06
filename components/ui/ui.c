#include "ui.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "bsp.h"
#include "esp_log.h"
#include "esp_lvgl_port.h"
#include "lvgl.h"

static const char *TAG = "ui";
static const size_t UI_DRAW_BUFFER_LINES = 50;

static lv_display_t *s_disp = NULL;
static lv_indev_t *s_indev = NULL;
static bool s_lvgl_ready = false;
static uint32_t s_touch_count = 0;

static lv_obj_t *s_label_status = NULL;
static lv_obj_t *s_label_packets = NULL;
static lv_obj_t *s_label_rssi = NULL;
static lv_obj_t *s_label_touch = NULL;

static void ui_set_label_text(lv_obj_t *label, const char *text)
{
    if (label == NULL) {
        return;
    }
    lv_label_set_text(label, text != NULL ? text : "");
}

static void ui_touch_test_event_cb(lv_event_t *event)
{
    if (lv_event_get_code(event) != LV_EVENT_CLICKED) {
        return;
    }

    s_touch_count++;

    char touch_buf[32];
    snprintf(touch_buf, sizeof(touch_buf), "Touches: %" PRIu32, s_touch_count);

    ui_set_label_text(s_label_status, "Touch pressed");
    ui_set_label_text(s_label_touch, touch_buf);
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
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x101820), 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);

    lv_obj_t *title = lv_label_create(scr);
    lv_label_set_text(title, "CSI Router Test UI");
    lv_obj_set_style_text_color(title, lv_color_hex(0xF2AA4C), 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_14, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 16);

    s_label_status = lv_label_create(scr);
    lv_label_set_text(s_label_status, "UI ready");
    lv_obj_set_style_text_color(s_label_status, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(s_label_status, LV_ALIGN_TOP_LEFT, 12, 60);

    s_label_packets = lv_label_create(scr);
    lv_label_set_text(s_label_packets, "Packets: 0");
    lv_obj_set_style_text_color(s_label_packets, lv_color_hex(0xC7D3DD), 0);
    lv_obj_align(s_label_packets, LV_ALIGN_TOP_LEFT, 12, 92);

    s_label_rssi = lv_label_create(scr);
    lv_label_set_text(s_label_rssi, "RSSI: -- dBm");
    lv_obj_set_style_text_color(s_label_rssi, lv_color_hex(0xC7D3DD), 0);
    lv_obj_align(s_label_rssi, LV_ALIGN_TOP_LEFT, 12, 118);

    s_label_touch = lv_label_create(scr);
    lv_label_set_text(s_label_touch, s_indev != NULL ? "Touches: 0" : "Touch: unavailable");
    lv_obj_set_style_text_color(s_label_touch, lv_color_hex(0xC7D3DD), 0);
    lv_obj_align(s_label_touch, LV_ALIGN_TOP_LEFT, 12, 144);

    lv_obj_t *button = lv_button_create(scr);
    lv_obj_set_size(button, 140, 48);
    lv_obj_align(button, LV_ALIGN_BOTTOM_MID, 0, -28);
    lv_obj_add_event_cb(button, ui_touch_test_event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *button_label = lv_label_create(button);
    lv_label_set_text(button_label, "Tap Me");
    lv_obj_center(button_label);

    lvgl_port_unlock();

    ESP_LOGI(TAG, "UI initialized");
    return ESP_OK;
}

void ui_set_status(const char *text)
{
    if (!s_lvgl_ready) {
        return;
    }

    if (s_label_status == NULL) {
        ESP_LOGI(TAG, "status: %s", text ? text : "");
        return;
    }

    lvgl_port_lock(0);
    ui_set_label_text(s_label_status, text);
    lvgl_port_unlock();
}

void ui_set_packets(uint32_t count)
{
    if (!s_lvgl_ready) {
        return;
    }

    char buf[32];
    snprintf(buf, sizeof(buf), "Packets: %" PRIu32, count);

    if (s_label_packets == NULL) {
        ESP_LOGI(TAG, "%s", buf);
        return;
    }

    lvgl_port_lock(0);
    ui_set_label_text(s_label_packets, buf);
    lvgl_port_unlock();
}

void ui_set_rssi(int rssi)
{
    if (!s_lvgl_ready) {
        return;
    }

    char buf[32];
    snprintf(buf, sizeof(buf), "RSSI: %d dBm", rssi);

    if (s_label_rssi == NULL) {
        ESP_LOGI(TAG, "%s", buf);
        return;
    }

    lvgl_port_lock(0);
    ui_set_label_text(s_label_rssi, buf);
    lvgl_port_unlock();
}

void ui_set_touch_point(uint16_t x, uint16_t y, bool touched)
{
    if (!s_lvgl_ready) {
        return;
    }

    char buf[48];
    if (touched) {
        snprintf(buf, sizeof(buf), "Touch: %u, %u", (unsigned)x, (unsigned)y);
    } else {
        snprintf(buf, sizeof(buf), "Touch: waiting");
    }

    if (s_label_touch == NULL || s_label_status == NULL) {
        ESP_LOGI(TAG, "%s", buf);
        return;
    }

    lvgl_port_lock(0);
    ui_set_label_text(s_label_touch, buf);
    if (touched) {
        ui_set_label_text(s_label_status, "Raw touch detected");
    }
    lvgl_port_unlock();
}

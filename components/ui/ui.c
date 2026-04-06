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
static const lv_coord_t UI_SCREEN_WIDTH = 172;
static const lv_coord_t UI_CARD_WIDTH = 156;

static lv_display_t *s_disp = NULL;
static lv_indev_t *s_indev = NULL;
static bool s_lvgl_ready = false;
static bool s_router_enabled = true;

static lv_obj_t *s_switch_router = NULL;
static lv_obj_t *s_label_network = NULL;
static lv_obj_t *s_label_status = NULL;
static lv_obj_t *s_label_rssi = NULL;
static lv_obj_t *s_label_touch = NULL;
static lv_obj_t *s_label_router_value = NULL;

static void ui_set_label_text(lv_obj_t *label, const char *text)
{
    if (label == NULL) {
        return;
    }
    lv_label_set_text(label, text != NULL ? text : "");
}

static lv_obj_t *ui_create_card(lv_obj_t *parent, lv_coord_t y, lv_coord_t height)
{
    lv_obj_t *card = lv_obj_create(parent);
    lv_obj_set_size(card, UI_CARD_WIDTH, height);
    lv_obj_align(card, LV_ALIGN_TOP_MID, 0, y);
    lv_obj_set_style_radius(card, 16, 0);
    lv_obj_set_style_border_width(card, 0, 0);
    lv_obj_set_style_bg_color(card, lv_color_hex(0xF5F7FA), 0);
    lv_obj_set_style_bg_opa(card, LV_OPA_COVER, 0);
    lv_obj_set_style_shadow_width(card, 12, 0);
    lv_obj_set_style_shadow_opa(card, LV_OPA_20, 0);
    lv_obj_set_style_shadow_color(card, lv_color_hex(0x10233A), 0);
    lv_obj_set_style_pad_all(card, 10, 0);
    return card;
}

static void ui_apply_router_state(bool enabled)
{
    s_router_enabled = enabled;

    if (s_switch_router != NULL) {
        if (enabled) {
            lv_obj_add_state(s_switch_router, LV_STATE_CHECKED);
        } else {
            lv_obj_remove_state(s_switch_router, LV_STATE_CHECKED);
        }
    }

    ui_set_label_text(s_label_router_value, enabled ? "Enabled" : "Disabled");
    ui_set_label_text(s_label_status, enabled ? "CSI router active" : "CSI router paused");
}

static void ui_router_switch_event_cb(lv_event_t *event)
{
    if (lv_event_get_code(event) != LV_EVENT_VALUE_CHANGED) {
        return;
    }

    lv_obj_t *sw = lv_event_get_target(event);
    ui_apply_router_state(lv_obj_has_state(sw, LV_STATE_CHECKED));
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
    lv_obj_set_style_bg_color(scr, lv_color_hex(0xDCE6EE), 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);

    lv_obj_t *hero = lv_obj_create(scr);
    lv_obj_set_size(hero, UI_CARD_WIDTH, 72);
    lv_obj_align(hero, LV_ALIGN_TOP_MID, 0, 8);
    lv_obj_set_style_radius(hero, 20, 0);
    lv_obj_set_style_border_width(hero, 0, 0);
    lv_obj_set_style_bg_color(hero, lv_color_hex(0x16324F), 0);
    lv_obj_set_style_bg_grad_color(hero, lv_color_hex(0x2B5C88), 0);
    lv_obj_set_style_bg_grad_dir(hero, LV_GRAD_DIR_VER, 0);
    lv_obj_set_style_shadow_width(hero, 16, 0);
    lv_obj_set_style_shadow_color(hero, lv_color_hex(0x10233A), 0);
    lv_obj_set_style_shadow_opa(hero, LV_OPA_30, 0);
    lv_obj_set_style_pad_all(hero, 12, 0);

    lv_obj_t *title = lv_label_create(scr);
    lv_label_set_text(title, "Control Dashboard");
    lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_14, 0);
    lv_obj_align_to(title, hero, LV_ALIGN_TOP_LEFT, 0, 2);

    s_label_status = lv_label_create(scr);
    lv_label_set_text(s_label_status, "CSI router active");
    lv_obj_set_style_text_color(s_label_status, lv_color_hex(0xD6E4F0), 0);
    lv_obj_set_style_text_font(s_label_status, &lv_font_montserrat_12, 0);
    lv_obj_align_to(s_label_status, hero, LV_ALIGN_TOP_LEFT, 0, 24);

    lv_obj_t *hero_caption = lv_label_create(scr);
    lv_label_set_text(hero_caption, "WaveShare ESP32-S3");
    lv_obj_set_style_text_color(hero_caption, lv_color_hex(0xA8C3DA), 0);
    lv_obj_set_style_text_font(hero_caption, &lv_font_montserrat_12, 0);
    lv_obj_align_to(hero_caption, hero, LV_ALIGN_TOP_LEFT, 0, 42);

    lv_obj_t *network_card = ui_create_card(scr, 90, 50);
    lv_obj_t *network_title = lv_label_create(network_card);
    lv_label_set_text(network_title, "Wi-Fi Network");
    lv_obj_set_style_text_color(network_title, lv_color_hex(0x667789), 0);
    lv_obj_set_style_text_font(network_title, &lv_font_montserrat_12, 0);
    lv_obj_align(network_title, LV_ALIGN_TOP_LEFT, 0, 0);

    s_label_network = lv_label_create(network_card);
    lv_label_set_text(s_label_network, "CSI_ROUTER_LAB");
    lv_obj_set_style_text_color(s_label_network, lv_color_hex(0x14293D), 0);
    lv_obj_set_style_text_font(s_label_network, &lv_font_montserrat_14, 0);
    lv_obj_align(s_label_network, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    lv_label_set_long_mode(s_label_network, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_width(s_label_network, UI_CARD_WIDTH - 20);

    lv_obj_t *router_card = ui_create_card(scr, 148, 58);
    lv_obj_t *router_title = lv_label_create(router_card);
    lv_label_set_text(router_title, "CSI Router");
    lv_obj_set_style_text_color(router_title, lv_color_hex(0x667789), 0);
    lv_obj_set_style_text_font(router_title, &lv_font_montserrat_12, 0);
    lv_obj_align(router_title, LV_ALIGN_TOP_LEFT, 0, 0);

    s_label_router_value = lv_label_create(router_card);
    lv_label_set_text(s_label_router_value, "Enabled");
    lv_obj_set_style_text_color(s_label_router_value, lv_color_hex(0x14293D), 0);
    lv_obj_set_style_text_font(s_label_router_value, &lv_font_montserrat_14, 0);
    lv_obj_align(s_label_router_value, LV_ALIGN_BOTTOM_LEFT, 0, 0);

    s_switch_router = lv_switch_create(router_card);
    lv_obj_align(s_switch_router, LV_ALIGN_RIGHT_MID, -2, 6);
    lv_obj_set_size(s_switch_router, 44, 24);
    lv_obj_add_state(s_switch_router, LV_STATE_CHECKED);
    lv_obj_add_event_cb(s_switch_router, ui_router_switch_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    lv_obj_t *signal_card = ui_create_card(scr, 214, 48);
    lv_obj_t *signal_title = lv_label_create(signal_card);
    lv_label_set_text(signal_title, "RSSI");
    lv_obj_set_style_text_color(signal_title, lv_color_hex(0x667789), 0);
    lv_obj_set_style_text_font(signal_title, &lv_font_montserrat_12, 0);
    lv_obj_align(signal_title, LV_ALIGN_TOP_LEFT, 0, 0);

    s_label_rssi = lv_label_create(signal_card);
    lv_label_set_text(s_label_rssi, "-42 dBm");
    lv_obj_set_style_text_color(s_label_rssi, lv_color_hex(0x14293D), 0);
    lv_obj_set_style_text_font(s_label_rssi, &lv_font_montserrat_14, 0);
    lv_obj_align(s_label_rssi, LV_ALIGN_BOTTOM_LEFT, 0, 0);

    s_label_touch = lv_label_create(scr);
    lv_label_set_text(s_label_touch, s_indev != NULL ? "Touch ready" : "Touch unavailable");
    lv_obj_set_style_text_color(s_label_touch, lv_color_hex(0x51606E), 0);
    lv_obj_set_style_text_font(s_label_touch, &lv_font_montserrat_12, 0);
    lv_obj_set_width(s_label_touch, UI_SCREEN_WIDTH - 24);
    lv_label_set_long_mode(s_label_touch, LV_LABEL_LONG_CLIP);
    lv_obj_align(s_label_touch, LV_ALIGN_BOTTOM_MID, 0, -6);

    ui_apply_router_state(true);

    lvgl_port_unlock();

    ESP_LOGI(TAG, "UI initialized");
    return ESP_OK;
}

void ui_set_network_name(const char *name)
{
    if (!s_lvgl_ready) {
        return;
    }

    if (s_label_network == NULL) {
        ESP_LOGI(TAG, "network: %s", name ? name : "");
        return;
    }

    lvgl_port_lock(0);
    ui_set_label_text(s_label_network, name != NULL ? name : "Unknown");
    lvgl_port_unlock();
}

void ui_set_router_enabled(bool enabled)
{
    if (!s_lvgl_ready) {
        return;
    }

    lvgl_port_lock(0);
    ui_apply_router_state(enabled);
    lvgl_port_unlock();
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
    (void)count;
}

void ui_set_rssi(int rssi)
{
    if (!s_lvgl_ready) {
        return;
    }

    char buf[32];
    snprintf(buf, sizeof(buf), "%d dBm", rssi);

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

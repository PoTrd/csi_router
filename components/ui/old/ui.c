#include "ui.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

#include "bsp.h"
#include "esp_log.h"
#include "esp_lvgl_port.h"
#include "lvgl.h"

static const char *TAG = "ui";

static lv_display_t *s_disp = NULL;
static lv_indev_t *s_indev = NULL;
static bool s_lvgl_ready = false;

static lv_obj_t *label_status = NULL;
static lv_obj_t *label_packets = NULL;
static lv_obj_t *label_rssi = NULL;

esp_err_t ui_init(void)
{
    const lvgl_port_cfg_t lvgl_cfg = ESP_LVGL_PORT_INIT_CONFIG();
    ESP_ERROR_CHECK(lvgl_port_init(&lvgl_cfg));
    s_lvgl_ready = true;

    if (bsp_get_panel() != NULL) {
        const lvgl_port_display_cfg_t disp_cfg = {
            .io_handle = bsp_get_panel_io(),
            .panel_handle = bsp_get_panel(),
            .buffer_size = BOARD_LCD_HRES * 20,
            .double_buffer = false,
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
                .buff_spiram = true,
                .swap_bytes = false,
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

    label_status = lv_label_create(scr);
    lv_label_set_text(label_status, "CSI routeur");
    lv_obj_align(label_status, LV_ALIGN_TOP_MID, 0, 10);

    label_packets = lv_label_create(scr);
    lv_label_set_text(label_packets, "Packets: 0");
    lv_obj_align(label_packets, LV_ALIGN_TOP_LEFT, 10, 50);

    label_rssi = lv_label_create(scr);
    lv_label_set_text(label_rssi, "RSSI: -- dBm");
    lv_obj_align(label_rssi, LV_ALIGN_TOP_LEFT, 10, 80);

    lvgl_port_unlock();

    ESP_LOGI(TAG, "UI initialized");
    return ESP_OK;
}

void ui_set_status(const char *text)
{
    if (!s_lvgl_ready) {
        return;
    }

    if (label_status == NULL) {
        ESP_LOGI(TAG, "status: %s", text ? text : "");
        return;
    }

    lvgl_port_lock(0);
    lv_label_set_text(label_status, text ? text : "");
    lvgl_port_unlock();
}

void ui_set_packets(uint32_t count)
{
    if (!s_lvgl_ready) {
        return;
    }

    char buf[32];
    snprintf(buf, sizeof(buf), "Packets: %" PRIu32, count);

    if (label_packets == NULL) {
        ESP_LOGI(TAG, "%s", buf);
        return;
    }

    lvgl_port_lock(0);
    lv_label_set_text(label_packets, buf);
    lvgl_port_unlock();
}

void ui_set_rssi(int rssi)
{
    if (!s_lvgl_ready) {
        return;
    }

    char buf[32];
    snprintf(buf, sizeof(buf), "RSSI: %d dBm", rssi);

    if (label_rssi == NULL) {
        ESP_LOGI(TAG, "%s", buf);
        return;
    }

    lvgl_port_lock(0);
    lv_label_set_text(label_rssi, buf);
    lvgl_port_unlock();
}

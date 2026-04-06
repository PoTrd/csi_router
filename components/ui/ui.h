#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t ui_init(void);
void ui_set_network_name(const char *name);
void ui_set_router_enabled(bool enabled);
void ui_set_status(const char *text);
void ui_set_packets(uint32_t count);
void ui_set_rssi(int rssi);
void ui_set_touch_point(uint16_t x, uint16_t y, bool touched);

#ifdef __cplusplus
}
#endif

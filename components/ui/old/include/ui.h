#pragma once

#include <stdint.h>

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t ui_init(void);
void ui_set_status(const char *text);
void ui_set_packets(uint32_t count);
void ui_set_rssi(int rssi);

#ifdef __cplusplus
}
#endif

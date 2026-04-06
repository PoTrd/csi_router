#include "csi_app.h"

#include <stdint.h>

#include "esp_check.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ui.h"

static const char *TAG = "csi_app";
static bool s_started = false;

static void csi_demo_task(void *arg)
{
    uint32_t packets = 0;
    int rssi = -42;

    ui_set_status("Demo running");

    while (true) {
        packets += 5;
        rssi--;
        if (rssi < -75) {
            rssi = -42;
        }

        ui_set_packets(packets);
        ui_set_rssi(rssi);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

esp_err_t csi_app_init(void)
{
    if (s_started) {
        return ESP_OK;
    }

    BaseType_t task_ok = xTaskCreate(
        csi_demo_task,
        "csi_demo_task",
        4096,
        NULL,
        5,
        NULL
    );
    ESP_RETURN_ON_FALSE(task_ok == pdPASS, ESP_ERR_NO_MEM, TAG, "failed to create demo task");

    s_started = true;
    ESP_LOGI(TAG, "CSI demo started");
    return ESP_OK;
}

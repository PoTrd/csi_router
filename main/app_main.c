#include "bsp.h"
#include "csi_app.h"
#include "nvs_flash.h"
#include "ui.h"

void app_main()
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_ERROR_CHECK(bsp_init());
    ESP_ERROR_CHECK(ui_init());
    ret = csi_app_init();
}

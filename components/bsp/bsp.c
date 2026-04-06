#include "bsp.h"

#include <stdbool.h>

#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_check.h"
#include "esp_lcd_jd9853.h"
#include "esp_lcd_touch_axs5106.h"
#include "esp_log.h"

static const char *TAG = "bsp";
static const spi_host_device_t BOARD_LCD_SPI_HOST = SPI2_HOST;
static const i2c_port_num_t BOARD_TOUCH_I2C_PORT = I2C_NUM_0;
static const uint32_t BOARD_TOUCH_I2C_SPEED_HZ = 400000;
static const size_t BOARD_LCD_DRAW_BUF_LINES = 40;

static esp_lcd_panel_io_handle_t s_panel_io = NULL;
static esp_lcd_panel_handle_t s_panel = NULL;
static esp_lcd_touch_handle_t s_touch = NULL;
static i2c_master_bus_handle_t s_i2c_bus = NULL;
static i2c_master_dev_handle_t s_i2c_touch_dev = NULL;
static bool s_initialized = false;

static esp_err_t bsp_enable_backlight(void)
{
#if CONFIG_BOARD_PIN_LCD_BL >= 0
    gpio_config_t backlight_cfg = {
        .pin_bit_mask = 1ULL << CONFIG_BOARD_PIN_LCD_BL,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_RETURN_ON_ERROR(gpio_config(&backlight_cfg), TAG, "backlight gpio config failed");
    ESP_RETURN_ON_ERROR(gpio_set_level(CONFIG_BOARD_PIN_LCD_BL, 1), TAG, "backlight enable failed");
#endif
    return ESP_OK;
}

static esp_err_t bsp_init_lcd(void)
{
    spi_bus_config_t bus_cfg = JD9853_PANEL_BUS_SPI_CONFIG(
        CONFIG_BOARD_PIN_LCD_SCLK,
        CONFIG_BOARD_PIN_LCD_MOSI,
        BOARD_LCD_HRES * BOARD_LCD_DRAW_BUF_LINES * sizeof(uint16_t)
    );
    esp_lcd_panel_io_spi_config_t io_cfg = JD9853_PANEL_IO_SPI_CONFIG(
        CONFIG_BOARD_PIN_LCD_CS,
        CONFIG_BOARD_PIN_LCD_DC,
        NULL,
        NULL
    );
    jd9853_vendor_config_t vendor_config = {
        .init_cmds = NULL,
        .init_cmds_size = 0,
    };
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = CONFIG_BOARD_PIN_LCD_RST,
        .rgb_endian = LCD_RGB_ENDIAN_BGR,
        .bits_per_pixel = 16,
        .vendor_config = &vendor_config,
        .flags = {
            .reset_active_high = 0,
        },
    };

    ESP_RETURN_ON_ERROR(spi_bus_initialize(BOARD_LCD_SPI_HOST, &bus_cfg, SPI_DMA_CH_AUTO), TAG, "spi init failed");
    ESP_RETURN_ON_ERROR(
        esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)BOARD_LCD_SPI_HOST, &io_cfg, &s_panel_io),
        TAG,
        "panel io init failed"
    );
    ESP_RETURN_ON_ERROR(esp_lcd_new_panel_jd9853(s_panel_io, &panel_config, &s_panel), TAG, "jd9853 init failed");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_reset(s_panel), TAG, "panel reset failed");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_init(s_panel), TAG, "panel init failed");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_disp_on_off(s_panel, true), TAG, "panel enable failed");

    ESP_LOGI(TAG, "LCD panel initialized");
    return ESP_OK;
}

static esp_err_t bsp_init_touch(void)
{
    i2c_master_bus_config_t bus_config = {
        .i2c_port = BOARD_TOUCH_I2C_PORT,
        .sda_io_num = CONFIG_BOARD_PIN_TOUCH_SDA,
        .scl_io_num = CONFIG_BOARD_PIN_TOUCH_SCL,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    i2c_device_config_t dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = ESP_LCD_TOUCH_IO_I2C_AXS5106_ADDRESS,
        .scl_speed_hz = BOARD_TOUCH_I2C_SPEED_HZ,
    };
    esp_lcd_touch_config_t touch_config = {
        .x_max = BOARD_LCD_HRES,
        .y_max = BOARD_LCD_VRES,
        .rst_gpio_num = (CONFIG_BOARD_PIN_TOUCH_RST >= 0) ? CONFIG_BOARD_PIN_TOUCH_RST : GPIO_NUM_NC,
        .int_gpio_num = (CONFIG_BOARD_PIN_TOUCH_INT >= 0) ? CONFIG_BOARD_PIN_TOUCH_INT : GPIO_NUM_NC,
        .levels = {
            .reset = 0,
            .interrupt = 0,
        },
        .flags = {
            .swap_xy = 0,
            .mirror_x = 0,
            .mirror_y = 0,
        },
    };

    ESP_RETURN_ON_ERROR(i2c_new_master_bus(&bus_config, &s_i2c_bus), TAG, "touch i2c bus init failed");
    ESP_RETURN_ON_ERROR(i2c_master_bus_add_device(s_i2c_bus, &dev_config, &s_i2c_touch_dev), TAG, "touch i2c device init failed");
    ESP_RETURN_ON_ERROR(esp_lcd_touch_new_i2c_axs5106(s_i2c_touch_dev, &touch_config, &s_touch), TAG, "touch init failed");

    ESP_LOGI(TAG, "Touch controller initialized");
    return ESP_OK;
}

esp_err_t bsp_init(void)
{
    if (s_initialized) {
        return ESP_OK;
    }

    ESP_RETURN_ON_ERROR(bsp_init_lcd(), TAG, "lcd init failed");
    ESP_RETURN_ON_ERROR(bsp_enable_backlight(), TAG, "backlight init failed");

    if (bsp_init_touch() != ESP_OK) {
        ESP_LOGW(TAG, "Touch controller init failed, continuing without touch");
        s_touch = NULL;
    }

    s_initialized = true;
    ESP_LOGI(TAG, "BSP initialized");
    return ESP_OK;
}

esp_lcd_panel_handle_t bsp_get_panel(void)
{
    return s_panel;
}

esp_lcd_panel_io_handle_t bsp_get_panel_io(void)
{
    return s_panel_io;
}

esp_lcd_touch_handle_t bsp_get_touch(void)
{
    return s_touch;
}

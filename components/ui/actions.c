#include "actions.h"
#include "screens.h"
#include "ui.h"
#include "esp_log.h"
#include "vars.h"
#include <string.h>
#include <stdint.h>

#include "ble_manager.h"

static const char *TAG = "ui_actions";

void action_enter_number_keypad(lv_event_t *e) {
    if (!e) return;

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target(e);

    if (code == LV_EVENT_PRESSED) {
        const char *number_pressed = NULL;
        if (btn) {
            lv_obj_t *label = lv_obj_get_child(btn, 0);
            if (label) {
                number_pressed = lv_label_get_text(label);
            }
        }

        if (!number_pressed || !number_pressed[0]) {
            ESP_LOGI(TAG, "action_enter_number: button pressed (no label) target=%p", btn);
            return;
        }

        ESP_LOGI(TAG, "Number pressed: %s", number_pressed);

        const char *current_pin = get_var_s_pin();
        int current_length = current_pin ? strlen(current_pin) : 0;

        if (current_length >= 4) {
            return;
        }

        char new_pin[5] = {0}; // Maximum length of PIN is 4 + null terminator
        strncpy(new_pin, current_pin, current_length);
        new_pin[current_length] = number_pressed[0];
        set_var_s_pin(new_pin);

        lv_obj_t *pin_code_objects[] = {
            objects.pin_code_1,
            objects.pin_code_2,
            objects.pin_code_3,
            objects.pin_code_4
        };

        if (pin_code_objects[current_length]) {
            ESP_LOGI(TAG, "PIN: %s", new_pin);
            lv_obj_set_style_bg_opa(pin_code_objects[current_length], 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

void action_backspace_keypad(lv_event_t *e) {
    if (!e) return;

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target(e);

    if (code == LV_EVENT_PRESSED) {
        ESP_LOGI(TAG, "Backspace pressed");

        const char *current_pin = get_var_s_pin();
        int current_length = current_pin ? strlen(current_pin) : 0;

        if (current_length <= 0) {
            return; // PIN is already empty
        }

        char new_pin[5] = {0}; // Maximum length of PIN is 4 + null terminator
        strncpy(new_pin, current_pin, current_length - 1);
        set_var_s_pin(new_pin);

        lv_obj_t *pin_code_objects[] = {
            objects.pin_code_1,
            objects.pin_code_2,
            objects.pin_code_3,
            objects.pin_code_4
        };

        if (pin_code_objects[current_length - 1]) {
            lv_obj_set_style_bg_opa(pin_code_objects[current_length - 1], 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }

        ESP_LOGI(TAG, "PIN after backspace: %s", new_pin);
    }
}

void action_validate_keypad(lv_event_t *e) {
    if (!e) return;

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target(e);

    if (code == LV_EVENT_PRESSED) {
        ESP_LOGI(TAG, "Validate pressed");

        const char *current_pin = get_var_s_pin();
        int current_length = current_pin ? strlen(current_pin) : 0;

        if (current_length < 4) {
            ESP_LOGI(TAG, "PIN is incomplete");
            return; // PIN is incomplete
        }

        lv_obj_t *pin_code_objects[] = {
            objects.pin_code_1,
            objects.pin_code_2,
            objects.pin_code_3,
            objects.pin_code_4
        };

        const char *correct_pin = "1234";
        if (strcmp(current_pin, correct_pin) == 0) {
            ESP_LOGI(TAG, "PIN is correct");
            set_var_s_pin("");
            create_screen_dashboard_page();
            lv_scr_load(objects.dashboard_page);
        } else {
            ESP_LOGI(TAG, "PIN is incorrect");
            set_var_s_pin("");
            for (int i = 0; i < 4; i++) {
                if (pin_code_objects[i]) {
                    lv_obj_set_style_bg_opa(pin_code_objects[i], 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
}

void action_lock_device(lv_event_t *e) {
    if (!e) return;

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target(e);
    if (code == LV_EVENT_PRESSED) {
        ESP_LOGI(TAG, "Lock button pressed");
        lv_scr_load(objects.security_page);
        ESP_LOGI(TAG, "Device locked");
    }
}

void action_navigate_bt_settings(lv_event_t *e) {
    if (!e) return;

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target(e);
    if (code == LV_EVENT_PRESSED) {
        ESP_LOGI(TAG, "Navigating to Bluetooth Settings");
        lv_scr_load(objects.bt_settings_page);
    }
}

void action_update_bt_connection(lv_event_t *e) {
    if (!e) return;

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target(e);
    if (code == LV_EVENT_PRESSED) {
        ESP_LOGI(TAG, "Updating Bluetooth connection");
        bool current_state = get_var_is_bt_connection_enable();
        set_var_is_bt_connection_enable(!current_state);
        if(!current_state) {
            ESP_LOGI(TAG, "Enabling Bluetooth");
            ble_manager_enable();
        } else {
            ESP_LOGI(TAG, "Disabling Bluetooth");
            ble_manager_disable();
        }
    }
}

/*
* Right swipe handling to go back
*/

static int16_t touch_start_x = 0;
static int16_t touch_start_y = 0;

void action_on_touch_pressed(lv_event_t * e) {
    if (!e) return;

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target(e);
    if (code == LV_EVENT_PRESSED) {
        lv_indev_t * indev = lv_indev_get_act();
        lv_point_t point;
        lv_indev_get_point(indev, &point);
        touch_start_x = point.x;
        touch_start_y = point.y;
    }
}

void action_on_touch_released(lv_event_t * e) {
    if (!e) return;

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target(e);
    if (code == LV_EVENT_RELEASED) {
        lv_indev_t * indev = lv_indev_get_act();
        lv_point_t point;
        lv_indev_get_point(indev, &point);
        int16_t delta_x = point.x - touch_start_x;
        int16_t delta_y = point.y - touch_start_y;

        const bool isRightSwipe = (delta_x > 50) && (abs(delta_y) < 30);
        if (isRightSwipe) {
            action_go_back(e);
        }
    }
}

/*
* Page navigation with history stack
*/
#define MAX_PAGES 15
static int page_stack[MAX_PAGES];
static int stack_top = -1;

static enum ScreensEnum get_active_page(void) {
    lv_obj_t *active = lv_scr_act();
    if (active == objects.security_page) return SCREEN_ID_SECURITY_PAGE;
    if (active == objects.dashboard_page) return SCREEN_ID_DASHBOARD_PAGE;
    if (active == objects.bt_settings_page) return SCREEN_ID_BT_SETTINGS_PAGE;
    return 0;
}

static void load_and_tick_page(enum ScreensEnum target_page) {
#if !defined(EEZ_FOR_LVGL)
    loadScreen(target_page);
#else
    lv_obj_t *screen = NULL;
    switch (target_page) {
        case SCREEN_ID_SECURITY_PAGE:
            screen = objects.security_page;
            break;
        case SCREEN_ID_DASHBOARD_PAGE:
            screen = objects.dashboard_page;
            break;
        case SCREEN_ID_BT_SETTINGS_PAGE:
            screen = objects.bt_settings_page;
            break;
        default:
            break;
    }
    if (screen) {
        lv_scr_load(screen);
    }
#endif
    tick_screen_by_id(target_page);
}

void action_go_to_page(lv_event_t * e) {
    if (!e) return;

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target(e);
    if (code == LV_EVENT_SHORT_CLICKED) {
        ESP_LOGI(TAG, "action_go_to_page triggered", code);
        int target_page_id = (int)(intptr_t)lv_event_get_user_data(e);
        enum ScreensEnum target_page = (enum ScreensEnum)target_page_id;

        if (target_page_id <= 0 || target_page_id > SCREEN_ID_BT_SETTINGS_PAGE) {
            ESP_LOGI(TAG, "Invalid target page ID: %d", target_page_id);
            return;
        }

        enum ScreensEnum current_page = get_active_page();
        if (current_page == target_page) {
            ESP_LOGI(TAG, "Already on target page ID: %d", target_page_id);
            return;
        }

        if (current_page != 0) {
            if (stack_top < MAX_PAGES - 1) {
                page_stack[++stack_top] = (int)current_page;
                ESP_LOGI(TAG, "Pushed page ID %d to stack. New stack top: %d", current_page, stack_top);
            } else {
                ESP_LOGW(TAG, "Page stack overflow, cannot push page ID %d", current_page);
            }
        } else {
            ESP_LOGW(TAG, "Active page unknown, not pushing to stack");
        }

        ESP_LOGI(TAG, "Navigating to page ID: %d", target_page_id);
        load_and_tick_page(target_page);
    }
}

void action_go_back(lv_event_t * e) {
    if (stack_top < 0) {
        ESP_LOGI(TAG, "No previous page to go back to");
        return;
    }

    enum ScreensEnum previous_page = (enum ScreensEnum)page_stack[stack_top--];
    ESP_LOGI(TAG, "Going back to page ID: %d", previous_page);
    load_and_tick_page(previous_page);
}

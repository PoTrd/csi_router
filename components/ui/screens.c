#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

void create_screen_security_page() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.security_page = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 172, 320);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff121826), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // btn_1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn_1 = obj;
            lv_obj_set_pos(obj, 17, 95);
            lv_obj_set_size(obj, 35, 35);
            lv_obj_add_event_cb(obj, action_enter_number_keypad, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff212936), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_btn_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_btn_1 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "1");
                }
            }
        }
        {
            // btn_2
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn_2 = obj;
            lv_obj_set_pos(obj, 69, 95);
            lv_obj_set_size(obj, 35, 35);
            lv_obj_add_event_cb(obj, action_enter_number_keypad, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff212936), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_btn_2
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_btn_2 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "2");
                }
            }
        }
        {
            // btn_3
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn_3 = obj;
            lv_obj_set_pos(obj, 121, 95);
            lv_obj_set_size(obj, 35, 35);
            lv_obj_add_event_cb(obj, action_enter_number_keypad, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff212936), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_btn_3
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_btn_3 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "3");
                }
            }
        }
        {
            // btn_4
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn_4 = obj;
            lv_obj_set_pos(obj, 17, 149);
            lv_obj_set_size(obj, 35, 35);
            lv_obj_add_event_cb(obj, action_enter_number_keypad, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff212936), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_btn_4
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_btn_4 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "4");
                }
            }
        }
        {
            // btn_5
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn_5 = obj;
            lv_obj_set_pos(obj, 69, 149);
            lv_obj_set_size(obj, 35, 35);
            lv_obj_add_event_cb(obj, action_enter_number_keypad, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff212936), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_btn_5
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_btn_5 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "5");
                }
            }
        }
        {
            // btn_6
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn_6 = obj;
            lv_obj_set_pos(obj, 121, 149);
            lv_obj_set_size(obj, 35, 35);
            lv_obj_add_event_cb(obj, action_enter_number_keypad, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff212936), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_btn_6
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_btn_6 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "6");
                }
            }
        }
        {
            // btn_7
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn_7 = obj;
            lv_obj_set_pos(obj, 17, 202);
            lv_obj_set_size(obj, 35, 35);
            lv_obj_add_event_cb(obj, action_enter_number_keypad, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff212936), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_btn_7
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_btn_7 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "7");
                }
            }
        }
        {
            // btn_8
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn_8 = obj;
            lv_obj_set_pos(obj, 69, 202);
            lv_obj_set_size(obj, 35, 35);
            lv_obj_add_event_cb(obj, action_enter_number_keypad, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff212936), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_btn_8
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_btn_8 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "8");
                }
            }
        }
        {
            // btn_9
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn_9 = obj;
            lv_obj_set_pos(obj, 121, 202);
            lv_obj_set_size(obj, 35, 35);
            lv_obj_add_event_cb(obj, action_enter_number_keypad, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff212936), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_btn_9
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_btn_9 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "9");
                }
            }
        }
        {
            // btn_back
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn_back = obj;
            lv_obj_set_pos(obj, 17, 256);
            lv_obj_set_size(obj, 35, 35);
            lv_obj_add_event_cb(obj, action_backspace_keypad, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff212936), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_btn_back
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_btn_back = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "B");
                }
            }
        }
        {
            // btn_0
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn_0 = obj;
            lv_obj_set_pos(obj, 69, 256);
            lv_obj_set_size(obj, 35, 35);
            lv_obj_add_event_cb(obj, action_enter_number_keypad, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff212936), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_btn_0
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_btn_0 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "0");
                }
            }
        }
        {
            // btn_validate
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn_validate = obj;
            lv_obj_set_pos(obj, 121, 256);
            lv_obj_set_size(obj, 35, 35);
            lv_obj_add_event_cb(obj, action_validate_keypad, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff4e80ee), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_btn_validate
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_btn_validate = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "V");
                }
            }
        }
        {
            // pin_code_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pin_code_1 = obj;
            lv_obj_set_pos(obj, 28, 54);
            lv_obj_set_size(obj, 20, 20);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff4e80ee), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3178f0), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pin_code_2
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pin_code_2 = obj;
            lv_obj_set_pos(obj, 60, 54);
            lv_obj_set_size(obj, 20, 20);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff4e80ee), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3178f0), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pin_code_3
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pin_code_3 = obj;
            lv_obj_set_pos(obj, 93, 54);
            lv_obj_set_size(obj, 20, 20);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff4e80ee), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3178f0), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pin_code_4
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pin_code_4 = obj;
            lv_obj_set_pos(obj, 125, 54);
            lv_obj_set_size(obj, 20, 20);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff4e80ee), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3178f0), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // label_enter_pin
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_enter_pin = obj;
            lv_obj_set_pos(obj, 34, 23);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Enter your PIN");
        }
    }
    
    tick_screen_security_page();
}

void tick_screen_security_page() {
}

void create_screen_dashboard_page() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.dashboard_page = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 172, 320);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff121826), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // label_dashboard_title
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_dashboard_title = obj;
            lv_obj_set_pos(obj, 13, 13);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Dashboard");
        }
        {
            // btn_lock
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn_lock = obj;
            lv_obj_set_pos(obj, 130, 6);
            lv_obj_set_size(obj, 30, 30);
            lv_obj_add_event_cb(obj, action_lock_device, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff212936), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_btn_10
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_btn_10 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "L");
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 13, 50);
            lv_obj_set_size(obj, 147, 142);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff212936), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_pin_set
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_pin_set = obj;
                    lv_obj_set_pos(obj, -4, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "PIN Set");
                }
                {
                    // value_is_pin_set
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.value_is_pin_set = obj;
                    lv_obj_set_pos(obj, -4, 25);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                }
                {
                    // label_number_bt_devices
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_number_bt_devices = obj;
                    lv_obj_set_pos(obj, 65, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "BT\nDevices");
                }
                {
                    // value_is_pin_set_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.value_is_pin_set_1 = obj;
                    lv_obj_set_pos(obj, 65, 40);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "0/3");
                }
                {
                    // label_number_passwords
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_number_passwords = obj;
                    lv_obj_set_pos(obj, -4, 79);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Passwords");
                }
                {
                    // value_number_passwords
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.value_number_passwords = obj;
                    lv_obj_set_pos(obj, -4, 95);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 13, 209);
            lv_obj_set_size(obj, 147, 47);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff212936), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_pin_settings
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_pin_settings = obj;
                    lv_obj_set_pos(obj, -1, 1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "PIN Settings");
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj2 = obj;
            lv_obj_set_pos(obj, 13, 274);
            lv_obj_set_size(obj, 147, 79);
            lv_obj_add_event_cb(obj, action_go_to_page, LV_EVENT_SHORT_CLICKED, (void *)3);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff212936), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_pin_settings_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_pin_settings_1 = obj;
                    lv_obj_set_pos(obj, 5, 9);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "BT\nSettings");
                }
            }
        }
    }
    
    tick_screen_dashboard_page();
}

void tick_screen_dashboard_page() {
    {
        const char *new_val = get_var_label_is_locked();
        const char *cur_val = lv_label_get_text(objects.value_is_pin_set);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.value_is_pin_set;
            lv_label_set_text(objects.value_is_pin_set, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_n_passwords();
        const char *cur_val = lv_label_get_text(objects.value_number_passwords);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.value_number_passwords;
            lv_label_set_text(objects.value_number_passwords, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_bt_settings_page() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.bt_settings_page = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 172, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            // label_dashboard_title_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_dashboard_title_1 = obj;
            lv_obj_set_pos(obj, 14, 14);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "BT\nSettings");
        }
        {
            // label_dashboard_title_2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_dashboard_title_2 = obj;
            lv_obj_set_pos(obj, 15, 82);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "BT \nconnection");
        }
        {
            lv_obj_t *obj = lv_switch_create(parent_obj);
            lv_obj_set_pos(obj, 112, 86);
            lv_obj_set_size(obj, 50, 25);
            lv_obj_add_event_cb(obj, action_update_bt_connection, LV_EVENT_PRESSED, (void *)0);
        }
        {
            // btn_back_1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn_back_1 = obj;
            lv_obj_set_pos(obj, 128, 14);
            lv_obj_set_size(obj, 35, 35);
            lv_obj_add_event_cb(obj, action_backspace_keypad, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff212936), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // label_btn_back_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_btn_back_1 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "B");
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 1, 0);
            lv_obj_set_size(obj, 85, 320);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_add_event_cb(obj, action_on_touch_pressed, LV_EVENT_PRESSED, (void *)0);
            lv_obj_add_event_cb(obj, action_on_touch_released, LV_EVENT_RELEASED, (void *)0);
        }
    }
    
    tick_screen_bt_settings_page();
}

void tick_screen_bt_settings_page() {
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_security_page,
    tick_screen_dashboard_page,
    tick_screen_bt_settings_page,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_security_page();
    create_screen_dashboard_page();
    create_screen_bt_settings_page();
}

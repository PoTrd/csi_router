#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *security_page;
    lv_obj_t *dashboard_page;
    lv_obj_t *bt_settings_page;
    lv_obj_t *btn_1;
    lv_obj_t *label_btn_1;
    lv_obj_t *btn_2;
    lv_obj_t *label_btn_2;
    lv_obj_t *btn_3;
    lv_obj_t *label_btn_3;
    lv_obj_t *btn_4;
    lv_obj_t *label_btn_4;
    lv_obj_t *btn_5;
    lv_obj_t *label_btn_5;
    lv_obj_t *btn_6;
    lv_obj_t *label_btn_6;
    lv_obj_t *btn_7;
    lv_obj_t *label_btn_7;
    lv_obj_t *btn_8;
    lv_obj_t *label_btn_8;
    lv_obj_t *btn_9;
    lv_obj_t *label_btn_9;
    lv_obj_t *btn_back;
    lv_obj_t *label_btn_back;
    lv_obj_t *btn_0;
    lv_obj_t *label_btn_0;
    lv_obj_t *btn_validate;
    lv_obj_t *label_btn_validate;
    lv_obj_t *pin_code_1;
    lv_obj_t *pin_code_2;
    lv_obj_t *pin_code_3;
    lv_obj_t *pin_code_4;
    lv_obj_t *label_enter_pin;
    lv_obj_t *label_dashboard_title;
    lv_obj_t *btn_lock;
    lv_obj_t *label_btn_10;
    lv_obj_t *obj0;
    lv_obj_t *label_pin_set;
    lv_obj_t *value_is_pin_set;
    lv_obj_t *label_number_bt_devices;
    lv_obj_t *value_is_pin_set_1;
    lv_obj_t *label_number_passwords;
    lv_obj_t *value_number_passwords;
    lv_obj_t *obj1;
    lv_obj_t *label_pin_settings;
    lv_obj_t *obj2;
    lv_obj_t *label_pin_settings_1;
    lv_obj_t *label_dashboard_title_1;
    lv_obj_t *label_dashboard_title_2;
    lv_obj_t *btn_back_1;
    lv_obj_t *label_btn_back_1;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_SECURITY_PAGE = 1,
    SCREEN_ID_DASHBOARD_PAGE = 2,
    SCREEN_ID_BT_SETTINGS_PAGE = 3,
};

void create_screen_security_page();
void tick_screen_security_page();

void create_screen_dashboard_page();
void tick_screen_dashboard_page();

void create_screen_bt_settings_page();
void tick_screen_bt_settings_page();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/
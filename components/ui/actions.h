#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_enter_number_keypad(lv_event_t * e);
extern void action_backspace_keypad(lv_event_t * e);
extern void action_validate_keypad(lv_event_t * e);
extern void action_lock_device(lv_event_t * e);
extern void action_navigate_bt_settings(lv_event_t * e);
extern void action_update_bt_connection(lv_event_t * e);
extern void action_on_touch_pressed(lv_event_t * e);
extern void action_on_touch_released(lv_event_t * e);
extern void action_go_to_page(lv_event_t * e);
extern void action_go_back(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/
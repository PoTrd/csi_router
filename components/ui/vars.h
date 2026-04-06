#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_IS_LOCKED = 0,
    FLOW_GLOBAL_VARIABLE_S_PIN = 1,
    FLOW_GLOBAL_VARIABLE_N_PASSWORDS = 2,
    FLOW_GLOBAL_VARIABLE_LABEL_IS_LOCKED = 3,
    FLOW_GLOBAL_VARIABLE_IS_BT_CONNECTION_ENABLE = 4
};

// Native global variables

extern bool get_var_is_locked();
extern void set_var_is_locked(bool value);
extern const char *get_var_s_pin();
extern void set_var_s_pin(const char *value);
extern const char *get_var_n_passwords();
extern void set_var_n_passwords(const char *value);
extern const char *get_var_label_is_locked();
extern void set_var_label_is_locked(const char *value);
extern bool get_var_is_bt_connection_enable();
extern void set_var_is_bt_connection_enable(bool value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/
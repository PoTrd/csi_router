#include "vars.h"
#include <string.h>

bool is_locked;

bool get_var_is_locked() {
    return is_locked;
}

char label_is_locked[100] = { 0 };

const char *get_var_label_is_locked() {
    const bool locked = get_var_is_locked();
    if (locked) {
        strcpy(label_is_locked, "True");
        return label_is_locked;
    }
    strcpy(label_is_locked, "False");
    return label_is_locked;
}

void set_var_label_is_locked(const char *value) {
    strncpy(label_is_locked, value, sizeof(label_is_locked) / sizeof(char));
    label_is_locked[sizeof(label_is_locked) / sizeof(char) - 1] = 0;
}

char s_pin[100] = { 0 };

const char *get_var_s_pin() {
    return s_pin;
}

void set_var_s_pin(const char *value) {
    strncpy(s_pin, value, sizeof(s_pin) / sizeof(char));
    s_pin[sizeof(s_pin) / sizeof(char) - 1] = 0;
}

char n_passwords[100] = { 0 };

const char *get_var_n_passwords() {
    return n_passwords;
}

void set_var_n_passwords(const char *value) {
    strncpy(n_passwords, value, sizeof(n_passwords) / sizeof(char));
    n_passwords[sizeof(n_passwords) / sizeof(char) - 1] = 0;
}

bool is_bt_connection_enable;

bool get_var_is_bt_connection_enable() {
    return is_bt_connection_enable;
}
void set_var_is_bt_connection_enable(bool value) {
    is_bt_connection_enable = value;
}

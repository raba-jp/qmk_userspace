/* Copyright 2024 ai03 Design Studio */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H
//      1......__2......__3......__4......__5......
#define _________________CUSTOM_L1_________________ KC_Q, KC_L, KC_U, KC_COMMA, KC_DOT
#define _________________CUSTOM_L2_________________ KC_E, KC_I, KC_A, KC_O, KC_MINUS
#define _________________CUSTOM_L3_________________ KC_Z, KC_X, KC_C, KC_V, KC_SLASH
#define _________________CUSTOM_R1_________________ KC_F, KC_W, KC_R, KC_Y, KC_P
#define _________________CUSTOM_R2_________________ KC_K, KC_T, KC_N, KC_S, KC_H
#define _________________CUSTOM_R3_________________ KC_G, KC_D, KC_M, KC_J, KC_B

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

enum layer_names {
    _BASE,
    _NAV,
    _SYMBOLS,
    _SYSTEM,
    _NUM,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//      0......__1......__2......__3......__4......__5......__6......__7......__8......__9......__10.....__11.....__12.....__13.....
    [_BASE] = LAYOUT_wrapper(
        KC_ESC,  _________________CUSTOM_L1_________________, KC_NO,   KC_NO,   _________________CUSTOM_R1_________________, MO(3),
        KC_TAB,  _________________CUSTOM_L2_________________, KC_NO,   KC_NO,   _________________CUSTOM_R2_________________, KC_NO,
        KC_LSFT, _________________CUSTOM_L3_________________, KC_NO,   KC_NO,   _________________CUSTOM_R3_________________, KC_RSFT,
                                   KC_LNG2, MO(1),   KC_SPC,  KC_TAB,  KC_BSPC, KC_ENT,  MO(1),   KC_LNG1
    ),

//      0......__1......__2......__3......__4......__5......__6......__7......__8......__9......__10.....__11.....__12.....__13.....
    [_NAV] = LAYOUT(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    _______,
        _______, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,
                                   _______, _______, _______, _______, _______, _______, _______, _______
    ),

//      0......__1......__2......__3......__4......__5......__6......__7......__8......__9......__10.....__11.....__12.....__13.....
    [_SYMBOLS] = LAYOUT(
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, _______, KC_ASTR, KC_AMPR, KC_LPRN, KC_RPRN, KC_CIRC, _______,
        _______, _______, _______, KC_BSLS, KC_COLN, KC_QUOT, _______, _______, KC_GRV,  KC_EQL,  KC_LBRC, KC_RBRC, _______, _______,
        _______, _______, _______, KC_PIPE, KC_SCLN, KC_DQT,  _______, _______, KC_TILD, KC_PLUS, KC_LCBR, KC_RCBR, _______, _______,
                                   _______, _______ , _______, _______, _______, _______, _______, _______
    ),

    [_SYSTEM] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_NUM] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_4,    KC_5,    KC_6,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_0,    KC_1,    KC_2,    KC_3,  _______, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______
    )
};

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
                       '*', '*', '*', '*', '*', '*', '*', '*'
    );

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_smtd(keycode, record)) {
        return false;
    }

    // your code here

    return true;
}

smtd_resolution on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        SMTD_MT(KC_E, KC_LEFT_CTRL)
        SMTD_MT(KC_I, KC_LEFT_ALT)
        SMTD_MT(KC_A, KC_LEFT_GUI)
        SMTD_MT(KC_O, KC_LSFT)
        SMTD_MT(KC_MINUS, KC_HYPR)
        SMTD_MT(KC_K, KC_HYPR)
        SMTD_MT(KC_T, KC_LSFT)
        SMTD_MT(KC_N, KC_RIGHT_GUI)
        SMTD_MT(KC_S, KC_RIGHT_ALT)
        SMTD_MT(KC_H, KC_RIGHT_CTRL)
        SMTD_LT(KC_SPACE, _SYMBOLS)
    }

    return SMTD_RESOLUTION_UNHANDLED;
}

/* Copyright 2024 ai03 Design Studio */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H
//      1......__2......__3......__4......__5......
#define _________________CUSTOM_L1_________________ KC_Q, KC_L, KC_U, KC_COMMA, KC_DOT
#define _________________CUSTOM_L2_________________ LCTL_T(KC_E), LALT_T(KC_I), LGUI_T(KC_A), LSFT_T(KC_O), HYPR_T(KC_MINUS)
#define _________________CUSTOM_L3_________________ KC_Z, KC_X, KC_C, KC_V, KC_SLASH
#define _________________CUSTOM_R1_________________ KC_F, KC_W, KC_R, KC_Y, KC_P
#define _________________CUSTOM_R2_________________ HYPR_T(KC_K), LSFT_T(KC_T), RGUI_T(KC_N), RALT_T(KC_S), RCTL_T(KC_H)
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
        LT(_NAV, KC_TAB), _________________CUSTOM_L2_________________, KC_NO, KC_NO, _________________CUSTOM_R2_________________, KC_NO,
        KC_LSFT, _________________CUSTOM_L3_________________, KC_NO,   KC_NO,   _________________CUSTOM_R3_________________, KC_RSFT,
                                   KC_LNG2, MO(1),   LT(_SYMBOLS, KC_SPC), LT(_NAV, KC_TAB), KC_BSPC, KC_ENT, MO(1), KC_LNG1
    ),

//      0......__1......__2......__3......__4......__5......__6......__7......__8......__9......__10.....__11.....__12.....__13.....
    [_NAV] = LAYOUT(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    _______,
        _______, LCTL_T(KC_F1), LALT_T(KC_F2), LGUI_T(KC_F3), LSFT_T(KC_F4), KC_F5, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______, _______,
        KC_F11,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,
                                   _______, _______, _______, _______, _______, _______, _______, _______
    ),

//      0......__1......__2......__3......__4......__5......__6......__7......__8......__9......__10.....__11.....__12.....__13.....
    // Selenium symbols: https://arthurin.github.io/keyboard-draw/#layer-symbols
    [_SYMBOLS] = LAYOUT(
        _______, KC_CIRC, KC_LABK, KC_RABK, KC_DLR,  KC_PERC, _______, _______, KC_AT,   KC_AMPR, KC_ASTR, KC_QUOT, KC_GRV,  _______,
        _______, KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, KC_EQL,  _______, _______, KC_BSLS, KC_PLUS, KC_MINUS,KC_SLASH,KC_DQT,  _______,
        _______, KC_TILD, KC_LBRC, KC_RBRC, KC_UNDS, KC_HASH, _______, _______, KC_PIPE, KC_EXLM, KC_SCLN, KC_COLN, KC_QUES, _______,
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

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    return keycode == LT(_SYMBOLS, KC_SPC) ? 180 : TAPPING_TERM;
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    return keycode == LT(_SYMBOLS, KC_SPC);
}

bool is_flow_tap_key(uint16_t keycode) {
    if ((get_mods() & (MOD_MASK_CG | MOD_BIT_LALT)) != 0) {
        return false;
    }

    // Include Minus, which is on this layout's home row.
    switch (get_tap_keycode(keycode)) {
        case KC_A ... KC_Z:
        case KC_COMM:
        case KC_DOT:
        case KC_SCLN:
        case KC_SLSH:
        case KC_MINUS:
        case KC_SPC:
            return true;
    }
    return false;
}

uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode) {
    // Keep layer access available even immediately after typing a letter.
    if (IS_QK_MOD_TAP(keycode) && is_flow_tap_key(keycode) && is_flow_tap_key(prev_keycode)) {
        return FLOW_TAP_TERM;
    }
    return 0;
}

/* Copyright 2024 ai03 Design Studio */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _NAV,
    _FUNC,
    _MANAGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        KC_ESC,  KC_Q,         KC_L,         KC_U,             KC_COMMA,     KC_DOT,          KC_NO, KC_NO,     KC_F,             KC_W,        KC_R,         KC_Y,         KC_P,          MO(3),
        KC_TAB,  LCTL_T(KC_E), LALT_T(KC_I), LGUI_T(KC_A),     LSFT_T(KC_O), ALL_T(KC_MINUS), KC_NO, KC_NO,     ALL_T(KC_K),      RSFT_T(KC_T), RGUI_T(KC_N), RALT_T(KC_S), RCTL_T(KC_H), KC_NO,
        KC_LCTL, KC_Z,         KC_X,         KC_C,             KC_V,         KC_SLASH,        KC_NO, KC_NO,     KC_G,             KC_D,         KC_M,         KC_J,         KC_B,         KC_RCTL,
                                             LCTL_T(KC_LNG2),  KC_NO,        LT(2, KC_SPACE), MO(1), KC_BSPC,   RSFT_T(KC_ENTER), KC_NO,        RCTL_T(KC_LNG1)
    ),

    [_NAV] = LAYOUT(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_FUNC] = LAYOUT(
        _______, LSFT(KC_1), LSFT(KC_2), LSFT(KC_3),    LSFT(KC_4),    LSFT(KC_5),     _______, _______, LSFT(KC_8),     LSFT(KC_7),     LSFT(KC_9),    LSFT(KC_0),        LSFT(KC_6), _______,
        _______, _______,    _______,    KC_BSLS,       LSFT(KC_SCLN), KC_QUOTE,       _______, _______, KC_GRAVE,       KC_EQUAL,       KC_LBRC,       KC_RBRC,       _______,    _______,
        _______, _______,    _______,    LSFT(KC_BSLS), KC_SCLN,       LSFT(KC_QUOTE), _______, _______, LSFT(KC_GRAVE), LSFT(KC_EQUAL), LSFT(KC_LBRC), LSFT(KC_RBRC), _______,    _______,
                                         _______,       _______,       _______,        _______, _______, _______,        _______,        _______
    ),

    [_MANAGE] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______
    )
};

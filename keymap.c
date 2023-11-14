#include QMK_KEYBOARD_H
#include "enums.h"
#include "layer.h"
#include "lufa.h"

static unit32_t oled_timer = 0;

bool user_led_enabled = true;

bool master_oled_cleared = false;

const unit16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
    KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T,                  KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
    KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G,                  KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
    KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B,                 KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSF,
            KC_LSHIFT, MO(_NUM), KC_SPC,                KC_ENT, MO(_UTILS), MO(_SYMBOL)
  ),

  [_NUM] = LAYOUT_split_3x6_3(
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,                  KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
    KC_TAB, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,             KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
    KC_LCTL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F12,
            KC_TRNS, KC_TRNS, KC_SPC,                 KC_ENT, KC_TRNS, KC_TRNS
  ),

  [_SYMBOL] = LAYOUT_split_3x6_3(
    KC_ESC, LSFT(KC_1),LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5), KC_LBRACKET, KC_RBRACKET, KC_EQUAL, KC_MINUS, KC_PLUS, KC_BSPC,
    KC_TAB, LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), LSFT(KC_MINUS), LSFT(KC_SLASH),LSFT(KC_LBRACKET), LSFT(KC_RBRACKET), KC_BSLASH, KC_L, KC_SCLN, KC_QUOT,
    KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B,                 LSFT(KC_9), LSFT(KC_0), KC_CAPSLOCK, KC_NO, KC_NO, KC_NO,
            KC_LSHIFT, KC_TRNS, KC_SPC,                KC_ENT, KC_TRNS, KC_TRNS
  ),

  [_UTILS] = LAYOUT_split_3x6_3(
    KC_ESC, KC_NO, KC_NO, KC_MYCM, KC_NO, KC_VOLU,                  KC_NO, KC_UP, KC_NO, KC_NO, KC_PGUP, KC_NO,
    KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO, KC_VOLD,                  KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDOWN, KC_NO, KC_NO,
    KC_LCTL, KC_NO, KC_NO, KC_NO, KC_NO, KC_MUTE,                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
             MO(_LED), MO(_LAYERS), KC_SPC,                KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_LED] = LAYOUT_split_3x6_3(
    RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                  KC_VOLU, KC_MPRV, KC_MNXT, KC_NO, KC_NO, KC_NO,
    RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO, KC_NO,       KC_VOLD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_NO, KC_NO,       KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
            KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_LAYERS] = LAYOUT_split_3x6_3(
    KC_ESC, MO(_GAMING), KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO, KC_UP, KC_NO, KC_NO, KC_NO, KC_BSPC,
    KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                        KC_LEFT, KC_DOWN, KC_RIGHT, KC_NO, KC_NO, KC_QUOT,
    KC_LCTL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
            KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_GAMING] = LAYOUT_split_3x6_3(
    KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T,                  KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
    KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G,                  KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
    KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B,                 KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSF,
            MO(_GAMING2), MO(_GAMING1), KC_SPC,                KC_ENT, KC_TRNS, KC_TRNS
  ),

  [_GAMING1] = LAYOUT_split_3x6_3(
    KC_ESC, KC_1, KC_W, KC_2, KC_3, KC_4,                  KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
    KC_TAB, KC_A, KC_S, KC_D, KC_5, KC_6,                  KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
    KC_LCTL, KC_Z, KC_X, KC_C, KC_7, KC_8,                 KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSF,
            KC_TRNS, KC_TRNS, KC_TRNS,                KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_GAMING2] = LAYOUT_split_3x6_3(
    MO(_NUM), KC_Y, KC_W, KC_U, KC_I, KC_O,                KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
    KC_TAB, KC_P, KC_S, KC_H, KC_K, KC_L,                  KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
    KC_LCTL, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,         KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSF,
            KC_TRNS, KC_TRNS, KC_TRNS,                KC_ENT, KC_TRNS, KC_TRNS
  ),
}
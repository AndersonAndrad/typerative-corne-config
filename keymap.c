#include QMK_KEYBOARD_H
#include "enums.h"
#include "layer.h"
#include "lufa.h"

static unit32_t oled_timer = 0;

bool user_led_enabled = true;

bool master_oled_cleared = false;

const unit16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
    KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T,                             KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
    KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G,                             KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
    KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B,                            KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSF,
            LSFT_T(KC_PGUP), MO(_NUM), KC_SPC,                   KC_ENT, MO(_SYMBOL), change
  )
}
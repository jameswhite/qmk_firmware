#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE   0 // default layer
#define LOWER  1 // symbols
#define RAISE  2 // media keys
#define ADJUST 3 // media keys

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_GRV,        KC_1,     KC_2,      KC_3,      KC_4,   KC_5,   KC_TRNS,
        KC_TAB,        KC_Q,     KC_W,      KC_E,      KC_R,   KC_T,   KC_TRNS,
        KC_ESC,        KC_A,     KC_S,      KC_D,      KC_F,   KC_G,
        KC_LSFT,       KC_Z,     KC_X,      KC_C,      KC_V,   KC_B,   KC_TRNS,
        KC_TRNS,   KC_LCTRL,  KC_LALT,   KC_LGUI, MO(LOWER),

                                                     KC_TRNS,  KC_TRNS,
                                                               KC_TRNS,
                                            KC_SPC,  KC_SPC,  KC_TRNS,

        // right hand
        KC_TRNS,    KC_6,   KC_7,  KC_8,      KC_9,      KC_0,       KC_DEL,
        KC_TRNS,    KC_Y,   KC_U,  KC_I,      KC_O,      KC_P,    KC_BSPACE,
                    KC_H,   KC_J,  KC_K,      KC_L,   KC_SCLN,      KC_QUOT,
        KC_TRNS,    KC_N,   KC_M,  KC_COMM, KC_DOT,   KC_SLSH,       KC_ENT,
                        MO(RAISE), KC_LEFT, KC_DOWN,    KC_UP,     KC_RIGHT,

        RESET,   KC_TRNS,
        KC_TRNS,
        KC_TRNS,   KC_SPC,KC_SPC
    ),

[LOWER] = LAYOUT_ergodox( // layer 1 : lower
       // left hand
       KC_TILD,   KC_EXLM,    KC_AT,  KC_HASH,   KC_DLR,  KC_PERC,  KC_TRNS,
       KC_TILD,   KC_EXLM,    KC_AT,  KC_HASH,   KC_DLR,  KC_PERC,  KC_TRNS,
       KC_DEL,      KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,
       KC_TRNS,     KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,  KC_TRNS,
       KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,

                                      KC_TRNS,   KC_TRNS,
                                                 KC_TRNS,
                               KC_SPC, KC_SPC,   KC_TRNS,

       // right hand
       KC_TRNS, KC_CIRC,   KC_AMPR,     KC_ASTR,     KC_LPRN,   KC_RPRN,  KC_BSPACE,
       KC_TRNS, KC_CIRC,   KC_AMPR,     KC_ASTR,     KC_LPRN,   KC_RPRN,  KC_DEL,
                  KC_F6,   KC_UNDS,     KC_PLUS,     KC_LCBR,   KC_RCBR,  KC_PIPE,
       KC_TRNS,  KC_F12,      KC_1,  S(KC_NUHS),  S(KC_NUBS),   KC_HOME,  KC_END,
                              MO(ADJUST),  KC_MNXT,   KC_VOLD,  KC_VOLU,  KC_MPLY,

       RESET, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_SPC, KC_SPC
),

[RAISE] = LAYOUT_ergodox( // layer 2 : raise
       // left hand
       KC_GRV,        KC_1,     KC_2,      KC_3,      KC_4,   KC_5,   KC_TRNS,
       KC_GRV,        KC_1,     KC_2,      KC_3,      KC_4,   KC_5,   KC_TRNS,
       KC_DEL,      KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,
       KC_TRNS,     KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,  KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(ADJUST),

                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_SPC, KC_SPC, KC_TRNS,

       // right hand
       KC_TRNS,    KC_6,     KC_7,       KC_8,         KC_9,        KC_0,      KC_BSPC,
       KC_TRNS,    KC_6,     KC_7,       KC_8,         KC_9,        KC_0,       KC_DEL,
                  KC_F6,  KC_MINS,      KC_EQL,     KC_LBRC,     KC_RBRC,      KC_BSLS,
       KC_TRNS,  KC_F12,     KC_1,  S(KC_NUHS),  S(KC_NUBS),     KC_PGUP,      KC_PGDN,
                              KC_TRNS,     KC_MNXT,   KC_VOLD,  KC_VOLU,  KC_MPLY,

       RESET, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_SPC, KC_SPC
),


[ADJUST] = LAYOUT_ergodox( // layer 3 : adjust
       // left hand
       KC_TRNS,  KC_F1,      KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,
       KC_TRNS,  RESET,      DEBUG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,

                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                    KC_SPC, KC_SPC, KC_TRNS,

       // right hand
       KC_F7,     KC_F8,     KC_F9,   KC_F10,  KC_F11,  KC_F12,   KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_DEL,
       KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,  KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_BTN1,  KC_BTN1,  KC_TRNS,  KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,

       RESET, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_SPC, KC_SPC
),



};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(LOWER)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      break;
    case 1:
      if (record->event.pressed) { // For resetting EEPROM
        eeconfig_init();
      }
      break;
  }
  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      default:
        break;
    }

  return state;
};

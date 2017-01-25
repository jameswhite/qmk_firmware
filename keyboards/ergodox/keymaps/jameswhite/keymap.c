#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
       // left hand
       KC_ESC,     KC_1,    KC_2,    KC_3,   KC_4,   KC_5,  KC_6,
       KC_TAB,     KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,   KC_LBRC,
       KC_LALT,    KC_A,    KC_S,    KC_D,   KC_F,   KC_G,
       KC_LSFT,    KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_LGUI,
       KC_LCTRL, KC_FN0, KC_LEFT, KC_RGHT, KC_FN0,
                                                         KC_LCTRL,  KC_LALT,
                                                                    KC_HOME,
                                                   KC_BSPC, KC_DEL,  KC_END,
        // right hand
              KC_GRV,  KC_7,     KC_8,     KC_9,    KC_0,  KC_MINS,   KC_EQL,
             KC_RBRC,  KC_Y,     KC_U,     KC_I,    KC_O,     KC_P,  KC_BSLS,
                       KC_H,     KC_J,     KC_K,     KC_L, KC_SCLN,  KC_QUOT,
             KC_LGUI,  KC_N,     KC_M,  KC_COMM,  KC_DOT,  KC_SLSH,  KC_RSFT,
                                 KC_FN0,  KC_UP, KC_DOWN,  KC_FN0,  KC_RCTRL,
        KC_RALT, KC_RCTL,
        KC_PGUP,
        KC_PGDN,  KC_ENT, KC_SPC
    ),
[MDIA] = KEYMAP(
        // left hand
        KC_FN3,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_MRWD, KC_MPLY, KC_MFFD,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_MUTE, KC_TRNS,
        KC_TRNS, KC_FN0,  KC_TRNS, KC_TRNS, KC_FN0,
                                         KC_TRNS, KC_TRNS,
                                                  KC_TRNS,
                                 KC_SPC,  KC_ENT, KC_TRNS,
        // right hand
             KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,  KC_F12, KC_FN4,
           KC_TRNS, KC_TRNS, KC_P7,  KC_P8,  KC_P9,  KC_PMNS, KC_TRNS,
                    KC_PAST, KC_P4,  KC_P5,  KC_P6,  KC_PPLS, KC_TRNS,
           KC_TRNS, KC_PSLS, KC_P1,  KC_P2,  KC_P3,  KC_PENT, KC_TRNS,
                            KC_FN0,  KC_P0, KC_DEL,   KC_FN0, KC_TRNS,
        KC_TRNS, KC_TRNS,
        KC_TRNS,
        KC_TRNS, KC_DEL, KC_BSPC
),
};

const uint16_t PROGMEM fn_actions[] = {
//    [0] = ACTION_LAYER_MOMENTARY(1),                      // FN0 - Activate Layer 1
//    [0] = ACTION_LAYER_TAP_TOGGLE(MDIA)                   // FN0 - Momentary Layer 1 (Media)
      [0] = ACTION_LAYER_MOMENTARY(MDIA)                    // FN0 - Momentary Layer 1 (Media)
//    [1] = ACTION_FUNCTION_TAP(COPY_KEY),                  // FN1 - LGui+C on tap, LGui on hold
//    [2] = ACTION_FUNCTION_TAP(PASTE_KEY),                 // FN2 - LGui+V on tap, LGui on hold
//    [3] = ACTION_MODS_KEY(MOD_LALT, KC_L),                // FN3 - Alt + L // Divvy left 1/3rd screen
//    [4] = ACTION_MODS_KEY(MOD_LALT | MOD_LSFT, KC_R),     // FN4 - ALT + Shift + rAlt + L // Divvy right 2/3rds screen
//    [5] = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_CAPS),         // FN5 - CAPSLOCK on tap, Left Shift on hold
//    [6] = ACTION_MODS_TAP_KEY(MOD_LALT, KC_CAPS),         // FN6 - CAPSLOCK on tap, Left Alt on hold
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

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};

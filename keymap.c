#include QMK_KEYBOARD_H
#include "keymap_danish.h"

// Define keymap layers
enum keymap_layers {
  _BASE,
  _SYM,
  _NUM,
  _FUN,
  _DK
};

// Define custom keycodes
enum keymap_custom_keycodes {
  WIN_TOG = SAFE_RANGE,  // WinKey toggle keycode
  MAC_TOG,               // Toggle Mac layout
  NEW_SAFE_RANGE
};

// Define mod keys
#define SYM MO(_SYM)
#define NUM MO(_NUM)
#define FUN MO(_FUN)
#define ENT_CTL LCTL_T(KC_ENT)


// User config 
typedef union {
  uint32_t raw;
  struct {
    bool mac_layout_enabled :1;
  };
} user_config_t;
user_config_t user_config;


// Init user settings
void keyboard_post_init_user(void) {
  user_config.raw = eeconfig_read_user(); // Read config from EEPROM
};


// For Win key toggle
bool win_key_enabled = true;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_ortho_4x12(
        DK_Q,    DK_W,    DK_E,    DK_R,    DK_T,    XXXXXXX, XXXXXXX, DK_Y,    DK_U,    DK_I,    DK_O,    DK_P,
        DK_A,    DK_S,    DK_D,    DK_F,    DK_G,    XXXXXXX, XXXXXXX, DK_H,    DK_J,    DK_K,    DK_L,    DK_QUOT,
        DK_Z,    DK_X,    DK_C,    DK_V,    DK_B,    XXXXXXX, XXXXXXX, DK_N,    DK_M,    KC_COMM, KC_DOT,  ENT_CTL,
        XXXXXXX, XXXXXXX, KC_LGUI, SYM,     KC_LSFT, XXXXXXX, XXXXXXX, KC_SPC,  NUM,     KC_LALT, XXXXXXX, XXXXXXX
    ),

    [_SYM] = LAYOUT_ortho_4x12(
        DK_EXLM, DK_AT,   DK_HASH, DK_DLR,  DK_PERC, XXXXXXX, XXXXXXX, DK_TILD, DK_DIAE, DK_LPRN, DK_RPRN, DK_COLN,
        DK_CIRC, DK_AMPR, DK_UNDS, DK_BSLS, DK_PIPE, XXXXXXX, XXXXXXX, XXXXXXX, DK_QUES, DK_LCBR, DK_RCBR, DK_SCLN,
        DK_PLUS, DK_MINS, DK_ASTR, DK_SLSH, DK_EQL,  XXXXXXX, XXXXXXX, DK_GRV,  DK_ACUT, DK_LBRC, DK_RBRC, _______,
        XXXXXXX, XXXXXXX, _______, _______, KC_LCTL, XXXXXXX, XXXXXXX, _______, FUN,     _______, XXXXXXX, XXXXXXX
    ),

    [_NUM] = LAYOUT_ortho_4x12(
        DK_1,    DK_2,    DK_3,    DK_4,    DK_5,    XXXXXXX, XXXXXXX, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_BSPC,
        DK_6,    DK_7,    DK_8,    DK_9,    DK_0,    XXXXXXX, XXXXXXX, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL,
        DK_PLUS, DK_MINS, DK_ASTR, DK_SLSH, DK_EQL,  XXXXXXX, XXXXXXX, KC_ESC,  XXXXXXX, KC_COMM, KC_DOT,  _______,
        XXXXXXX, XXXXXXX, _______, _______, _______, XXXXXXX, XXXXXXX, _______, _______, _______, XXXXXXX, XXXXXXX
    ),

    [_FUN] = LAYOUT_ortho_4x12(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXXX, XXXXXXX, RESET,   KC_VOLU, KC_INS,  XXXXXXX, KC_PSCR,
        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MAC_TOG, DK_AE,   DK_OSTR, DK_ARNG,
        XXXXXXX, XXXXXXX, _______, _______, _______, XXXXXXX, XXXXXXX, _______, _______, _______, XXXXXXX, XXXXXXX 
    ),

    [_DK] = LAYOUT_ortho_4x12(
        XXXXXXX, XXXXXXX, WIN_TOG, XXXXXXX, RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MAC_TOG, XXXXXXX, DK_AE,   DK_OSTR, DK_ARNG,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};


// This is a hack to match US keycap legends on a Danish keyboard layout - using Key Override
const key_override_t shift_comm_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, DK_LABK);
const key_override_t shift_dot_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, DK_RABK);
const key_override_t shift_quot_key_override = ko_make_basic(MOD_MASK_SHIFT, DK_QUOT, DK_DQUO);
//const key_override_t shift_scln_key_override = ko_make_basic(MOD_MASK_SHIFT, DK_SCLN, DK_COLN); 
//const key_override_t shift_slsh_key_override = ko_make_basic(MOD_MASK_SHIFT, DK_SLSH, DK_QUES); 

// Key Override array
const key_override_t **key_overrides = (const key_override_t *[]){
    &shift_comm_key_override,
    &shift_dot_key_override,
    &shift_quot_key_override,
    //&shift_scln_key_override,
    //&shift_slsh_key_override,
    NULL
};


// SYSTEM layer activation
// layer_state_t layer_state_set_user(layer_state_t state) {
//   return update_tri_layer_state(state, _SYM, _NUM, _DK);
// }

// Process custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    case MAC_TOG: // Mac toggle
      if (record->event.pressed) {
        user_config.mac_layout_enabled ^= 1; // Toggles the status
        eeconfig_update_user(user_config.raw); // Writes to EEPROM!
      }
      return false;
      break;

    case WIN_TOG: // Windows Key toggle
      if (record->event.pressed) { // Toggle Windows Key
        win_key_enabled ^= 1;
      }
      return false;
      break;
    
    case KC_LGUI: // Check if Windows Key is disabled 
      if (!win_key_enabled && !user_config.mac_layout_enabled) {
        return false;
      } else {
        return true;
      }
      break;
    
    case DK_AT: // @: PC ALGR(KC_2), Mac LALT(KC_NUHS)
      if(user_config.mac_layout_enabled) {
        if (record->event.pressed) {
          register_code16(LALT(KC_NUHS));
        } else {
          unregister_code16(LALT(KC_NUHS));
        }
        return false;
      } else {
        return true;
      }
      break;
    
    case DK_DLR: // $: PC ALGR(KC_4), Mac LSFT(LALT(KC_3))
      if(user_config.mac_layout_enabled) {
        if (record->event.pressed) {
          register_code16(LSFT(LALT(KC_3)));
        } else {
          unregister_code16(LSFT(LALT(KC_3)));
        }
        return false;
      } else {
        return true;
      }
      break;
    
    case DK_BSLS: // (backslash): PC ALGR(KC_NUBS), Mac LSFT(LALT(KC_7))
      if(user_config.mac_layout_enabled) {
        if (record->event.pressed) {
          register_code16(LSFT(LALT(KC_7)));
        } else {
          unregister_code16(LSFT(LALT(KC_7)));
        }
        return false;
      } else {
        return true;
      }
      break;

    case DK_PIPE: // |: PC ALGR(KC_EQL), Mac LALT(KC_I)
      if(user_config.mac_layout_enabled) {
        if (record->event.pressed) {
          register_code16(LALT(DK_I));
        } else {
          unregister_code16(LALT(DK_I));
        }
        return false;
      } else {
        return true;
      }
      break;

    case DK_LCBR: // {: PC ALGR(KC_7), Mac LSFT(LALT(KC_8))
      if(user_config.mac_layout_enabled) {
        if (record->event.pressed) {
          register_code16(LSFT(LALT(KC_8)));
        } else {
          unregister_code16(LSFT(LALT(KC_8)));
        }
        return false;
      } else {
        return true;
      }
      break;

    case DK_RCBR: // }: PC ALGR(KC_0), Mac LSFT(LALT(KC_9))
      if(user_config.mac_layout_enabled) {
        if (record->event.pressed) {
          register_code16(LSFT(LALT(KC_9)));
        } else {
          unregister_code16(LSFT(LALT(KC_9)));
        }
        return false;
      } else {
        return true;
      }
      break;

  }
  return true;
};

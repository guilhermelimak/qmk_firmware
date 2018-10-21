#include "tadahw.h"

#define _______ KC_TRNS

// Layers
#define _BASE 0
#define _GAME 1
#define _FN 2

// Aliases
#define ESC_FN LT(_FN, KC_ESC)
#define GRV_FN LT(_FN, KC_GRV)

// Layers tap dance
enum
{
  LYR = 0,
  BRT = 1
};

bool fn_held;
void dance_layers(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->pressed)
  {
    layer_on(_FN);
    fn_held = true;
    return;
  }

  switch (state->count)
  {
    case 1:
      breathing_self_disable();
      // Only base layer on
      if (!state->pressed)
      {
        layer_off(_GAME);
        layer_off(_FN);
        fn_held = false;
      }

      break;

    case 2:
      breathing_period_set(1);
      breathing_enable();
      layer_on(_FN);
      layer_off(_GAME);
      break;

    case 3:
      breathing_period_set(6);
      breathing_enable();
      layer_on(_GAME);
      layer_off(_FN);
      break;
  }
}

void dance_layers_finish(qk_tap_dance_state_t *state, void *user_data)
{
  if (fn_held)
  {
    layer_off(_FN);
    fn_held = false;
  }
}

void dance_breath_rate(qk_tap_dance_state_t *state, void *user_data)
{
  breathing_period_set(state->count);
  breathing_enable();
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [BRT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_breath_rate, NULL),
    [LYR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_layers, dance_layers_finish)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap _BASE: Default Layer
    * ,----------------------------------------------------------------.
    * |~ ` | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Del |
    * |----------------------------------------------------------------|
    * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Home|
    * |----------------------------------------------------------------|
    * |Esc fn1|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
    * |----------------------------------------------------------------|
    * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
    * |----------------------------------------------------------------|
    * |Ctrl|Alt |Win |        Space          |Alt|LYR|Ctrl|Lef|Dow|Rig |
    * `----------------------------------------------------------------'
    */
    [_BASE] = LAYOUT_ansi(
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_DEL,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
        ESC_FN, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGUP,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN,
        KC_LCTL, KC_LALT, KC_LWIN, KC_SPC, KC_RALT, TD(LYR), KC_RCTRL, KC_LEFT, KC_DOWN, KC_RGHT),

    /* 1 - Keymap _GAME: Gaming layer
    * ,----------------------------------------------------------------.
    * |`~  | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Del |
    * |----------------------------------------------------------------|
    * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Home|
    * |----------------------------------------------------------------|
    * |Esc    |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
    * |----------------------------------------------------------------|
    * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
    * |----------------------------------------------------------------|
    * |Ctrl|Alt |Win |        Space          |Alt| LYR|Ctrl|Lef|Dow|Rig |
    * `----------------------------------------------------------------'
    */
    // This layer exists to fix an issue where esc is not recognized properly on games if it's also
    // used to change to a layer on LT
    [_GAME] = LAYOUT_ansi(
        GRV_FN , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_ESC , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    /* 2 - Keymap _FN: Function Layer
    * ,----------------------------------------------------------------.
    * |   | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12| Del   |    |
    * |----------------------------------------------------------------|
    * |     |prev|play|next|   |   |   |   |   |   |   |   |   |   |   |
    * |----------------------------------------------------------------|
    * |     |vol+|Mute|vol-|   |   |   |Lft|Dwn|Up|Rght|   |      |    |
    * |----------------------------------------------------------------|
    * |      |Bl- |BL |BL+ |BRT|   |   |   |   |   |   |      |   |    |
    * |----------------------------------------------------------------|
    * |winunl|winlck|     |     BL_TOGGLE    |   |LYR|    |   |   |    |
    * `----------------------------------------------------------------'
    */
    [_FN] = LAYOUT_ansi(
        _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, _______,
        _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,  _______, _______, _______, _______,
        _______, BL_DEC , BL_BRTG, BL_INC , TD(BRT), _______, _______, _______, _______, _______, _______, _______, _______, _______,
 MAGIC_UNNO_GUI, MAGIC_NO_GUI, _______,                 BL_TOGG              , _______, _______, _______, _______, _______, _______),

};

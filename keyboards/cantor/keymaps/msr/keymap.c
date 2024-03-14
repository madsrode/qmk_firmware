// SPDX-License-Identifier: GPL-2.0

#include QMK_KEYBOARD_H
#include "keymap_danish.h"
#include "print.h"

// typedef enum {
//     TD_NONE,
//     TD_UNKNOWN,
//     TD_SINGLE_TAP,
//     TD_SINGLE_HOLD,
//     TD_DOUBLE_TAP,
//     TD_DOUBLE_HOLD,
//     TD_DOUBLE_SINGLE_TAP, // Send two single taps
//     TD_TRIPLE_TAP,
//     TD_TRIPLE_HOLD
// } td_state_t;

// typedef struct {
//     bool is_press_action;
//     td_state_t state;
// } td_tap_t;

// // Tap dance enums
// enum {
//     X_CTL,
//     WIN_DANCE,
//     COMM_DANCE,
// };

// td_state_t tabesc_dance(tap_dance_state_t *state);
// void tabesc_finished(tap_dance_state_t *state, void *user_data);
// void tabesc_reset(tap_dance_state_t *state, void *user_data);

// td_state_t entwin_dance(tap_dance_state_t *state);
// void entwin_finished(tap_dance_state_t *state, void *user_data);
// void entwin_reset(tap_dance_state_t *state, void *user_data);

// #define COMM_HOME LT(0, KC_COMM)
// #define DK_ARNG_LEFT LT(0, DK_ARNG)
// #define MPLY_MNXT LT(0, KC_MPLY)

// // Helper for implementing tap vs. long-press keys. Given a tap-hold
// // key event, replaces the hold function with `long_press_keycode`.
// static bool process_tap_or_long_press_key(keyrecord_t* record, uint16_t long_press_keycode) {
//   if (record->tap.count == 0) {  // Key is being held.
//     if (record->event.pressed) {
//       uprint("process_tap_or_long_press_key sent\n");
//       tap_code16(long_press_keycode);
//     }
//     uprint("process_tap_or_long_press_key false\n");
//     return false;  // Skip default handling.
//   }

//     uprint("process_tap_or_long_press_key true");
//   return true;  // Continue default handling.
// }

// layer_state_t layer_state_set_user(layer_state_t state) {
//   uprintf("LS: %u\n", state);
//   if(state == 0) {
//       tap_code16(MEH(KC_0));
//   }
//   else if(state == 8) {
//       tap_code16(MEH(KC_8));
//   }
//   return state;
// }

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  static bool lt0_is_held = false;
  static bool LCTL_is_held = false;


#ifdef CONSOLE_ENABLE
  uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif 

  switch (keycode) {
    case LT(3, KC_SPC):
        lt0_is_held = record->event.pressed;
        uprintf("LT0: %u\n", lt0_is_held);
        return true;
    case KC_LCTL:
        LCTL_is_held = record->event.pressed;
        uprintf("LT0: %u\n", LCTL_is_held);
        return true;
    case KC_HOME:
    case KC_END:
        uprintf("LT0: %u %u\n", lt0_is_held, LCTL_is_held);
        if (lt0_is_held && LCTL_is_held) {
            print("string\n");
            return false;
        }
        return true;
        
    // case COMM_HOME:  // Comma on tap, Ctrl+C on long press.
    //   return process_tap_or_long_press_key(record, C(KC_HOME));

    // case DK_ARNG_LEFT:  // Dot on tap, Alt+Left on long press.
    //   return process_tap_or_long_press_key(record, LALT(KC_LEFT));

    // case MPLY_MNXT:  // Play/pause on tap, next song on long press.
    //   return process_tap_or_long_press_key(record, KC_MNXT);

    // Other macros...
  }

  return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      
    [0] = LAYOUT_split_3x6_3(
        KC_TAB,      DK_ARNG,   KC_COMM,   DK_DOT,    DK_P,       DK_Y,                               DK_F,       DK_G,       DK_C,      DK_R,      DK_L,      KC_BSPC,
        KC_LSFT,     KC_A,      KC_O,      DK_E,      DK_U,       DK_I,                               DK_D,       DK_H,       DK_T,      DK_N,      DK_S,      KC_DEL,
        KC_LCTL,     DK_AE,     DK_Q,      DK_J,      DK_K,       DK_X,                               DK_B,       DK_M,       DK_W,      DK_V,      DK_Z,      KC_RSFT,
                                                         KC_LALT, LT(3, KC_SPC), KC_LGUI,          LT(2, KC_ENT), LT(1, KC_SPC), LT(4, KC_X)
                                                        //  KC_LALT, LT(3, KC_SPC), LT(6, KC_LGUI),          LT(2, KC_ENT), LT(1, KC_SPC), LT(4, KC_X)
    ),
     /*
      * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
      * │Tab│ Å │ , │ . │ P │ Y │       │ F │ G │ C │ R │ L │Bsp│
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │Sft│ A │ O │ E │ U │ I │       │ D │ H │ T │ N │ S │Del│
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │Ctl│ Æ │ Q │ J │ K │ X │       │ B │ M │ W │ V │ Z │Sft│
      * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
      *               ┌───┐                   ┌───┐
      *               │   ├───┐           ┌───┤   │
      *               └───┤   ├───┐   ┌───┤   ├───┘
      *                   └───┤   │   │   ├───┘
      *                       └───┘   └───┘
      */

    [1] = LAYOUT_split_3x6_3(
        ALGR(KC_EQL), DK_QUES, DK_LCBR, DK_RCBR, DK_QUOT,   DK_DQUO,                         DK_GRV,     DK_ACUT,  DK_AT,     DK_HASH,   DK_PERC,   KC_BSPC,
        KC_LSFT,      DK_LABK, DK_LPRN, DK_RPRN, DK_MINS,   DK_UNDS,                         DK_EURO,    DK_DLR,   DK_AMPR,   DK_EQL,    DK_PLUS,   DK_EXLM,
        KC_LCTL,      DK_RABK, DK_LBRC, DK_RBRC, DK_BSLS,   DK_SLSH,                         KC_NO,      DK_CIRC,  DK_TILD,   DK_HALF,   DK_SECT,   KC_RSFT,
                                                         KC_LALT,  KC_NO , KC_NO,          KC_NO, KC_NO, KC_NO
    ),

    /*
      * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
      * │ | │ ? │ { │ } │ ' │ " │       │ ´ │ ` │ @ │ # │ % │   │
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │Sft│ < │ ( │ ) │ - │ _ │       │ € │ $ │ & │ = │ + │ ! │
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │Ctl│ > │ [ │ ] │ \ │ / │       │   │ ^ │ ~ │ ½ │ § │   │
      * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
      *               ┌───┐                   ┌───┐
      *               │   ├───┐           ┌───┤   │
      *               └───┤   ├───┐   ┌───┤   ├───┘
      *                   └───┤   │   │   ├─x─┘
      *                       └───┘   └───┘
      *   DK_DIAE DK_CURR DK_PND
      */

    [2] = LAYOUT_split_3x6_3(
        KC_NO,       KC_NO,      C(KC_HOME), DK_DOT,   C(KC_END),  KC_NO,                              DK_PLUS,    DK_7,      DK_8,     DK_9,     DK_MINS,  KC_BSPC,
        KC_LSFT,     KC_F2,      KC_F3,     KC_F4,     KC_F5,      KC_F6,                              DK_ASTR,    DK_4,      DK_5,     DK_6,     DK_0,     DK_DOT,
        KC_LCTL,     KC_F8,      KC_F9,     KC_F10,    KC_F11,     KC_F12,                             DK_SLSH,    DK_1,      DK_2,     DK_3,     KC_ENT,   KC_NO,
                                                         KC_LALT,  KC_NO, KC_NO,          KC_NO, QK_BOOT, QK_RBT
    ),
      /*
      * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
      * │   │   │ , │ . │   │   │       │ + │ 7 │ 8 │ 9 │ - │Bsp│
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │   │F2 │F3 │F4 │F5 │F6 │       │ * │ 4 │ 5 │ 6 │ 0 │   │
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │   │F8 │F9 │F10│F11│F12│       │ / │ 1 │ 2 │ 3 │Ent│   │
      * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
      *               ┌───┐                   ┌───┐
      *               │   ├───┐           ┌───┤   │
      *               └───┤   ├───┐   ┌───┤   ├───┘
      *                   └───┤   │   │   ├───┘
      *                       └───┘   └─x─┘
      *   
      */

    [3] = LAYOUT_split_3x6_3(
        KC_TAB,      KC_NO,      KC_HOME,    KC_UP,     KC_END,      KC_PGUP,                          KC_NO,      DK_7,      DK_8,     DK_9,   KC_NO,     KC_BSPC,
        KC_LSFT,     KC_LALT,    KC_LEFT,    KC_DOWN,   KC_RGHT,     KC_PGDN,                          KC_NO,      DK_4,      DK_5,     DK_6,   DK_0,      KC_NO,
        KC_LCTL,     KC_NO,      KC_BTN1,    KC_BTN2,   DK_K,        DK_X,                             KC_NO,      DK_1,      DK_2,     DK_3,   KC_NO,     KC_RSFT,
                                                         KC_LALT,  KC_NO, KC_LGUI,          KC_NO, KC_NO, KC_LGUI
    ),

      /*
      * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
      * │Tab│   │Hme│Up │End│PgU│       │ + │ 7 │ 8 │ 9 │ - │Bsp│
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │Sft│Alt│Lft│Dwn│Rgh│PgD│       │ * │ 4 │ 5 │ 6 │ 0 │   │
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │Ctl│   │MB1│MB2│ K │ X │       │ / │ 1 │ 2 │ 3 │Ent│Sft│
      * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
      *               ┌───┐                   ┌───┐
      *               │   ├───┐           ┌───┤   │
      *               └───┤   ├───┐   ┌───┤   ├───┘
      *                   └─x─┤   │   │   ├───┘
      *                       └───┘   └───┘
      *   
      */

    [4] = LAYOUT_split_3x6_3(
        KC_NO,       KC_NO,      KC_NO,     KC_NO,     KC_NO,      KC_NO,                              KC_NO,      KC_HOME,    KC_UP,     KC_END,    KC_NO,     KC_BSPC,
        KC_LSFT,     KC_NO,      KC_NO,     KC_NO,     KC_NO,      KC_NO,                              KC_PGUP,    KC_LEFT,    KC_DOWN,   KC_RGHT,   KC_NO,     KC_NO,
        KC_LCTL,     KC_NO,      KC_NO,     KC_NO,     KC_NO,      KC_NO,                              KC_PGDN,    KC_BTN1,    KC_BTN2,   KC_NO,     KC_NO,     KC_RSFT,
                                                        KC_LALT,  KC_NO, KC_LGUI,          KC_NO, KC_NO, KC_NO
    ),

      /*
      * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
      * │   │   │   │   │   │   │       │   │Hme│Up │End│   │Bsp│
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │   │   │   │   │   │   │       │PgU│Lft│Dwn│Rgh│   │   │
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │   │   │   │   │   │   │       │PgD│MB1│MB2│   │   │Sft│
      * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
      *               ┌───┐                   ┌───┐
      *               │   ├───┐           ┌───┤   │
      *               └───┤   ├───┐   ┌───┤   ├─x─┘
      *                   └───┤   │   │   ├───┘
      *                       └───┘   └───┘
      *   
      */

    [5] = LAYOUT_split_3x6_3(
        KC_NO,       KC_NO,      C(KC_HOME), DK_DOT,   C(KC_END),  KC_NO,                              DK_PLUS,    DK_7,      DK_8,     DK_9,     DK_MINS,  KC_BSPC,
        KC_LSFT,     KC_F2,      A(KC_LEFT), KC_F4,    A(KC_RGHT), KC_F6,                              DK_ASTR,    DK_4,      DK_5,     DK_6,     DK_0,     DK_DOT,
        KC_LCTL,     KC_F8,      KC_F9,     KC_F10,    KC_F11,     KC_F12,                             DK_SLSH,    DK_1,      DK_2,     DK_3,     KC_ENT,   KC_NO,
                                                         KC_NO,  KC_NO, KC_NO,          KC_NO, KC_NO, KC_NO
    ),
      /*
      * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
      * │   │   │ , │ . │   │   │       │ + │ 7 │ 8 │ 9 │ - │Bsp│
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │   │F2 │F3 │F4 │F5 │F6 │       │ * │ 4 │ 5 │ 6 │ 0 │   │
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │   │F8 │F9 │F10│F11│F12│       │ / │ 1 │ 2 │ 3 │Ent│   │
      * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
      *               ┌───┐                   ┌───┐
      *               │   ├───┐           ┌───┤   │
      *               └───┤   ├───┐   ┌───┤   ├───┘
      *                   └───┤   │   │   ├───┘
      *                       └───┘   └───┘
      *   
      */

    [6] = LAYOUT_split_3x6_3(
        KC_NO,       KC_NO,      C(KC_HOME), DK_DOT,   C(KC_END),  KC_NO,                              DK_PLUS,    DK_7,      DK_8,     DK_9,     DK_MINS,  KC_BSPC,
        KC_LSFT,     KC_2,      A(KC_LEFT), KC_F4,    A(KC_RGHT), KC_F6,                              DK_ASTR,    DK_4,      DK_5,     DK_6,     DK_0,     DK_DOT,
        KC_LCTL,     KC_F8,      KC_F9,     KC_F10,    KC_F11,     KC_F12,                             DK_SLSH,    DK_1,      DK_2,     DK_3,     KC_ENT,   KC_NO,
                                                         KC_NO,  KC_NO, KC_NO,          KC_NO, KC_NO, KC_NO
    ),
      /*
      * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
      * │   │   │ , │ . │   │   │       │ + │ 7 │ 8 │ 9 │ - │Bsp│
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │   │F2 │F3 │F4 │F5 │F6 │       │ * │ 4 │ 5 │ 6 │ 0 │   │
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │   │F8 │F9 │F10│F11│F12│       │ / │ 1 │ 2 │ 3 │Ent│   │
      * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
      *               ┌───┐                   ┌───┐
      *               │   ├───┐           ┌───┤   │
      *               └───┤   ├───┐   ┌───┤   ├───┘
      *                   └───┤   │   │   ├───┘
      *                       └───┘   └───┘
      *   
      */
};

const uint16_t PROGMEM combo_TabArng[] = {KC_TAB, DK_ARNG, COMBO_END};
const uint16_t PROGMEM combo_OE[] = {KC_O, KC_E, COMBO_END}; // Ctrl + C
const uint16_t PROGMEM combo_EU[] = {KC_E, KC_U, COMBO_END}; // Ctrl + V
const uint16_t PROGMEM combo_OU[] = {KC_O, KC_U, COMBO_END}; // Ctrl + X
const uint16_t PROGMEM combo_QJ[] = {KC_Q, KC_J, COMBO_END}; // Ctrl + Z
const uint16_t PROGMEM combo_JK[] = {KC_J, KC_K, COMBO_END}; // Ctrl + Y
const uint16_t PROGMEM combo_AO[] = {KC_A, KC_O, COMBO_END}; // Ctrl + A
const uint16_t PROGMEM combo_KX[] = {KC_K, KC_X, COMBO_END}; // Toggle layer 3
const uint16_t PROGMEM combo_AeQ[] = {DK_AE, KC_Q, COMBO_END}; // Ø
const uint16_t PROGMEM combo_DotP[] = {DK_DOT, KC_P, COMBO_END}; // MO(4)
const uint16_t PROGMEM combo_AU[] = {DK_A, KC_U, COMBO_END}; // MO(4)
const uint16_t PROGMEM combo_CommDot[] = {DK_COMM, DK_DOT, COMBO_END}; // Toggle layer 5

combo_t key_combos[] = {
    COMBO(combo_TabArng, MO(5)),
    COMBO(combo_OE, LCTL(KC_C)),
    COMBO(combo_EU, LCTL(KC_V)), 
    COMBO(combo_OU, LCTL(KC_X)), 
    COMBO(combo_QJ, LCTL(KC_Z)),
    COMBO(combo_JK, LCTL(KC_Y)), 
    COMBO(combo_AO, LCTL(KC_A)), 
    COMBO(combo_KX, TG(3)), 
    COMBO(combo_AeQ, DK_OSTR), 
    COMBO(combo_DotP, MO(4)), 
    COMBO(combo_AU, KC_ESC),
    COMBO(combo_CommDot, OSL(5)),   
};

// Create an instance of 'td_tap_t' for the 'x' tap dance.
// static td_tap_t tabesctap_state = {
//     .is_press_action = true,
//     .state = TD_NONE
// };

// td_state_t tabesc_dance(tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
//         // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
//         else return TD_SINGLE_HOLD;
//     } else if (state->count == 2) {
//         // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tapS
//         // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
//         // keystrokes of the key, and not the 'double tap' action/macro.
//         if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
//         else if (state->pressed) return TD_DOUBLE_HOLD;
//         else return TD_DOUBLE_TAP;
//     }

//     // Assumes no one is trying to type the same letter three times (at least not quickly).
//     // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
//     // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
//     if (state->count == 3) {
//         if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
//         else return TD_TRIPLE_HOLD;
//     } else return TD_UNKNOWN;
// }

// void tabesc_finished(tap_dance_state_t *state, void *user_data) {
//     tabesctap_state.state = tabesc_dance(state);
//     switch (tabesctap_state.state) {
//         case TD_SINGLE_TAP: register_code(KC_TAB); break;
//         case TD_SINGLE_HOLD: register_code(KC_ESC); break;
//         case TD_DOUBLE_TAP: register_code(KC_ESC); break;
//         case TD_DOUBLE_HOLD: register_code(KC_LALT); break;
//         // Last case is for fast typing. Assuming your key is `f`:
//         // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
//         // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
//         case TD_DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X); break;
//         default: break;
//     }
// }

// void tabesc_reset(tap_dance_state_t *state, void *user_data) {
//     switch (tabesctap_state.state) {
//         case TD_SINGLE_TAP: unregister_code(KC_TAB); break;
//         case TD_SINGLE_HOLD: unregister_code(KC_ESC); break;
//         case TD_DOUBLE_TAP: unregister_code(KC_ESC); break;
//         case TD_DOUBLE_HOLD: unregister_code(KC_LALT);
//         case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X);
//         default: break;
//     }
//     tabesctap_state.state = TD_NONE;
// }

// // Create an instance of 'td_tap_t' for the 'x' tap dance.
// static td_tap_t entwintap_state = {
//     .is_press_action = true,
//     .state = TD_NONE
// };

// td_state_t entwin_dance(tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
//         // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
//         else return TD_SINGLE_HOLD;
//     } else if (state->count == 2) {
//         // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tapS
//         // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
//         // keystrokes of the key, and not the 'double tap' action/macro.
//         if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
//         else if (state->pressed) return TD_DOUBLE_HOLD;
//         else return TD_DOUBLE_TAP;
//     }

//     // Assumes no one is trying to type the same letter three times (at least not quickly).
//     // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
//     // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
//     if (state->count == 3) {
//         if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
//         else return TD_TRIPLE_HOLD;
//     } else return TD_UNKNOWN;
// }

// void entwin_finished(tap_dance_state_t *state, void *user_data) {
//     entwintap_state.state = entwin_dance(state);
//     switch (entwintap_state.state) {
//         case TD_SINGLE_TAP:  break;
//         case TD_SINGLE_HOLD: layer_on(4); register_code(KC_LGUI); break;
//         case TD_DOUBLE_HOLD: layer_on(4); register_code(KC_LGUI); break;
//         // Last case is for fast typing. Assuming your key is `f`:
//         // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
//         // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
//         case TD_DOUBLE_SINGLE_TAP: tap_code(KC_ENT); register_code(KC_ENT); break;
//         default: break;
//     }
// }

// void entwin_reset(tap_dance_state_t *state, void *user_data) {
//     switch (entwintap_state.state) {
//         case TD_SINGLE_TAP:  break;
//         case TD_SINGLE_HOLD: layer_off(4); unregister_code(KC_LGUI); break;
//         case TD_DOUBLE_HOLD: layer_off(4); unregister_code(KC_LGUI); break;
//         case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X); break;
//         default: break;
//     }
//     entwintap_state.state = TD_NONE;
// }

// tap_dance_action_t tap_dance_actions[] = {
//     [X_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tabesc_finished, tabesc_reset),
//     [WIN_DANCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, entwin_finished, entwin_reset)
// };



#include "common.h"
#include "keycodes.c"
#include "hrm_fix.c"

enum layers {
    _BASE = 0,
    _BASE_HRM,
    _GAME,
    _SYMNUM,
    _SYMNUM_HRM,
    _NAV,
    _FUNC,
    _GAME_NUM,
    _GAME_NUM_PAD,
};

#define RESET_TIMEOUT 2000

#define MY_SYMNUM_ESC LT(_SYMNUM, KC_ESC)
#define MY_SYMNUM_TAB LT(_SYMNUM, KC_TAB)
#define MY_NAV MO(_NAV)
#define MY_FUNC MO(_FUNC)
#define MY_GM_NUM OSL(_GAME_NUM)
#define MY_GM_NUMP MO(_GAME_NUM_PAD)

#define MY_SCR_SHOT LSFT(LCMD(KC_4))
#define MY_Z_IN  LCMD(KC_EQL)
#define MY_Z_OUT LCMD(KC_MINS)
#define MY_Z_RST LCMD(KC_0)
#define MY_T_PREV LCMD(KC_LCBR)
#define MY_T_NEXT LCMD(KC_RCBR)
#define MY_BACK LCMD(KC_LBRC)
#define MY_FWD LCMD(KC_RBRC)

#define HRM_MOD1(key) LT(_SYMNUM_HRM, key)
#define HRM_MOD2(key) LOPT_T(key)
#define HRM_MOD3(key) LCMD_T(key)
#define HRM_MOD4(key) LSFT_T(key)
#define HRM_MOD5(key) (key)

#define HM_A HRM_MOD1(KC_A)
#define HM_S HRM_MOD2(KC_S)
#define HM_D HRM_MOD3(KC_D)
#define HM_F HRM_MOD4(KC_F)
#define HM_G HRM_MOD5(KC_G)

#define HM_H HRM_MOD5(KC_H)
#define HM_J HRM_MOD4(KC_J)
#define HM_K HRM_MOD3(KC_K)
#define HM_L HRM_MOD2(KC_L)
#define HM_SCLN HRM_MOD1(KC_SCLN)

#define HM_Z KC_Z
#define HM_V LT(_NAV, KC_V)
#define HM_M LT(_NAV, KC_M)
#define HM_SLSH KC_SLSH

#define HM_1 KC_1
#define HM_2 HRM_MOD2(KC_2)
#define HM_3 HRM_MOD3(KC_3)
#define HM_4 HRM_MOD4(KC_4)
#define HM_5 KC_5

#define HM_EQL KC_EQL
#define HM_LPRN HRMF_LSFT_LPRN
#define HM_RPRN HRMF_LCMD_RPRN
#define HM_ASTR HRMF_LOPT_ASTR
#define HM_BSLS KC_BSLS

#ifdef LEADER_ENABLE
#  define MY_LEAD KC_LEAD
#else
#  define MY_LEAD XXXXXXX
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * BASE
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  BS    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * | LCtrl  |      |      |      |      |      |                              |      |      |      |      |      | RCtrl  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  | Lead | AltGr|  | `    | Play |   N  |   M  | ,  < | . >  | /  ? |  - _   |
 * | LShift |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | Opt  | Cmd  | Nav  | Space|SymNum|  |SymNum| Enter| Nav  | Cmd  | Opt  |
 *                        |      |      |      |      | Esc  |  | Tab  |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_BASE] = LAYOUT(
      KC_TAB,    KC_Q,   KC_W,   KC_E,    KC_R,    KC_T,                                                    KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
      KC_LCTRL,  KC_A,   KC_S,   KC_D,    KC_F,    KC_G,                                                    KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, RCTL_T(KC_QUOT),
      KC_LSFT,   KC_Z,   KC_X,   KC_C,    KC_V,    KC_B,   MY_LEAD, KC_RALT,        KC_GRV,        KC_MPLY, KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_MINS),
                                 KC_LOPT, KC_LCMD, MY_NAV, KC_SPC,  MY_SYMNUM_ESC,  MY_SYMNUM_TAB, KC_ENT,  MY_NAV, KC_LCMD, KC_LOPT
    ),
/*
 * BASE w/ HOME ROW MODS
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * | LCtrl  |SymNum| Opt  | Cmd  | Shft |      |                              |      | Shft | Cmd  | Opt  |SymNum| RCtrl  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |      |      |  |      |      |   N  |   M  | ,  < | . >  | /  ? |        |
 * | LShift |      |      |      | Nav  |      |      |      |  |      |      |      | Nav  |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_BASE_HRM] = LAYOUT(
      _______, KC_Q,   KC_W,   KC_E,    KC_R,    KC_T,                                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
      _______, HM_A,   HM_S,   HM_D,    HM_F,    HM_G,                                         HM_H,    HM_J,    HM_K,    HM_L,    HM_SCLN, _______,
      _______, HM_Z,   KC_X,   KC_C,    HM_V,    KC_B,    _______, _______,  _______, _______, KC_N,    HM_M,    KC_COMM, KC_DOT,  HM_SLSH, _______,
                               _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______
    ),
/*
 * GAME
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  BS    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | Ctrl   |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | Esc  |      |  | Base | Play |   N  |   M  | ,  < | . >  | /  ? |  - _   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | Gui  | Alt  | NumP | Space| Num  |  |SymNum| Enter| Nav  | Alt  | Gui  |
 *                        |      |      |      |      |      |  | Tab  |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GAME] = LAYOUT(
      KC_TAB,    KC_Q,   KC_W,   KC_E,    KC_R,    KC_T,                                                   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
      KC_LCTRL,  KC_A,   KC_S,   KC_D,    KC_F,    KC_G,                                                   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT,   KC_Z,   KC_X,   KC_C,    KC_V,    KC_B,       KC_ESC, _______,    TO(_BASE),     KC_MPLY, KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
                                 KC_LGUI, KC_LALT, MY_GM_NUMP, KC_SPC, MY_GM_NUM,  MY_SYMNUM_TAB, KC_ENT,  MY_NAV, KC_RALT, KC_RGUI
    ),
/*
 * SYMNUM
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | !    | @    | %    | ^    | $    |                              | &    | {    | }    | |    | `    |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | 1    | 2    | 3    | 4    | 5    |                              | =    | (    | )    | *    | \    |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | 6    | 7    | 8    | 9    | 0    |      |      |  |      |      | #    | [    | ]    | ~    | +    |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYMNUM] = LAYOUT(
      _______, KC_EXLM, KC_AT, KC_PERC, KC_CIRC, KC_DLR,                                       KC_AMPR, KC_LCBR, KC_RCBR, KC_PIPE, KC_GRV,  _______,
      _______, KC_1,    KC_2,  KC_3,    KC_4,    KC_5,                                         KC_EQL,  KC_LPRN, KC_RPRN, KC_ASTR, KC_BSLS, _______,
      _______, KC_6,    KC_7,  KC_8,    KC_9,    KC_0,    _______, _______,  _______, _______, KC_HASH, KC_LBRC, KC_RBRC, KC_TILD, KC_PLUS, _______,
                               _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______
    ),
/*
 * SYMNUM w/ HOME ROW MODS
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | !    | @    | %    | ^    | $    |                              | &    | {    | }    | |    | `    |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | 1    | 2    | 3    | 4    | 5    |                              | =    | (    | )    | *    | \    |        |
 * | LCtrl  |      | Opt  | Cmd  | Shft |      |                              |      | Shft | Cmd  | Opt  |      | RCtrl  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | 6    | 7    | 8    | 9    | 0    |      |      |  |      |      | #    | [    | ]    | ~    | +    |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYMNUM_HRM] = LAYOUT(
      _______, KC_EXLM, KC_AT, KC_PERC, KC_CIRC, KC_DLR,                                       KC_AMPR, KC_LCBR, KC_RCBR, KC_PIPE, KC_GRV,  _______,
      _______, HM_1,    HM_2,  HM_3,    HM_4,    HM_5,                                         HM_EQL,  HM_LPRN, HM_RPRN, HM_ASTR, HM_BSLS, _______,
      _______, KC_6,    KC_7,  KC_8,    KC_9,    KC_0,    _______, _______,  _______, _______, KC_HASH, KC_LBRC, KC_RBRC, KC_TILD, KC_PLUS, _______,
                               _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______
    ),
/*
 * NAV
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | Func   | MW Up| Clk 2| M Up | Clk 1| Clk 3|                              | Pnt S|      | Up   |      | Home | Func   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | MW Dn| M Lft| M Dn | M Rgt| V Up |                              | Pg Up| Left | Down | Right| End  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | MW Lf| MW Rt| Prev | Next | V Dn | Scr S|      |  | Z Rst| Mute | Pg Dn| Prv T| Nxt T| Back | Fwd  |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      | Clk 1| Clk 2| Clk 3|  | Zoom | Zoom |      |      |      |
 *                        |      |      |      |      |      |  | Out  | In   |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      MY_FUNC, KC_MS_WH_UP,   KC_MS_BTN2,     KC_MS_U, KC_MS_BTN1, KC_MS_BTN3,                                              KC_PSCR, _______,   KC_UP,     _______, KC_HOME, MY_FUNC,
      _______, KC_MS_WH_DOWN, KC_MS_L,        KC_MS_D, KC_MS_R,    KC_VOLU,                                                 KC_PGUP, KC_LEFT,   KC_DOWN,   KC_RGHT, KC_END,  _______,
      _______, KC_MS_WH_LEFT, KC_MS_WH_RIGHT, KC_MPRV, KC_MNXT,    KC_VOLD,    MY_SCR_SHOT, _______,     MY_Z_RST, KC_MUTE, KC_PGDN, MY_T_PREV, MY_T_NEXT, MY_BACK, MY_FWD,  _______,
                                              _______, _______,    KC_MS_BTN1, KC_MS_BTN2,  KC_MS_BTN3,  MY_Z_OUT, MY_Z_IN, _______, _______, _______
    ),
/*
 * FUNC
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      | MS A0| MS A1| MS A2|      |                              | F1   | F2   | F3   | F4   | F5   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | TOG  | SAI  | HUI  | VAI  | MOD  |                              | F6   | F7   | F8   | F9   | F10  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |Static| SAD  | HUD  | VAD  | RMOD | Reset|      |  | Game | Reset| F11  | F12  |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_FUNC] = LAYOUT(
      _______, _______, KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2, _______,                                           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,
      _______, RGB_TOG, RGB_SAI,      RGB_HUI,      RGB_VAI,      RGB_MOD,                                           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      _______, RGB_M_P, RGB_SAD,      RGB_HUD,      RGB_VAD,      RGB_RMOD, MY_RESET, _______,  TO(_GAME), MY_RESET, KC_F11,  KC_F12,  _______, _______, _______, _______,
                                      _______,      _______,       _______, _______,  _______,  _______,   _______,  _______, _______, _______
    ),
/*
 * GAME_NUM
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | 1    | 2    | 3    | 4    | 5    |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | 6    | 7    | 8    | 9    | 0    |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GAME_NUM] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        _______, _______, _______, _______, _______, _______,
      _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Layer template
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      | Num 7| Num 8| Num 9|      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      | Num 4| Num 5| Num 6|      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | Num 0| Num 1| Num 2| Num 3|      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GAME_NUM_PAD] = LAYOUT(
      _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, KC_KP_4, KC_KP_4, KC_KP_6, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, KC_KP_0, KC_KP_7, KC_KP_8, KC_KP_7, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};


uint32_t reset_timer = 0;

void reset_with_message(void) {
  reset_timer = timer_read32();
}

void handle_reset(void) {
  oled_write_P(PSTR("Bootloader mode\n\n\n\n\n\n\n\n"), false);

  if (timer_elapsed32(reset_timer) > RESET_TIMEOUT) {
    reset_keyboard();
  }
}

#ifdef RGBLIGHT_LAYERS

#define LED_COUNT 20
const rgblight_segment_t PROGMEM my_symnum_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, LED_COUNT, HSV_BLUE} );
const rgblight_segment_t PROGMEM my_nav_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, LED_COUNT, HSV_GREEN} );
const rgblight_segment_t PROGMEM my_func_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, LED_COUNT, HSV_MAGENTA} );
const rgblight_segment_t PROGMEM my_game_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, LED_COUNT, HSV_RED} );
const rgblight_segment_t PROGMEM my_game_num_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, LED_COUNT, HSV_PINK} );
const rgblight_segment_t PROGMEM my_game_num_pad_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, LED_COUNT, HSV_YELLOW} );

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
  my_symnum_layer,
  my_nav_layer,
  my_func_layer,
  my_game_layer,
  my_game_num_layer,
  my_game_num_pad_layer
);

#endif

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_LAYERS
  rgblight_layers = my_rgb_layers;
#endif
}

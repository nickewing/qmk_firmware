/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#include "./common.c"

#define CURRENT_MESSAGE_TIMEOUT 1500
const char *current_message = 0;
uint32_t current_message_timer = 0;

/* #endif */

#ifdef LEADER_ENABLE
bool leader_mode = false;
bool leader_success = false;
#endif

#ifdef COMBO_ENABLE

enum combos {
  /* MY_COMBO_Q_W, */
  MY_COMBO_W_E,
  MY_COMBO_E_R,
  MY_COMBO_R_T,

  /* MY_COMBO_A_S, */
  MY_COMBO_S_D,
  MY_COMBO_D_F,
  MY_COMBO_F_G,

  MY_COMBO_X_C,
  MY_COMBO_C_V,
  MY_COMBO_V_B,

  MY_COMBO_U_I,
  MY_COMBO_I_O,

  MY_COMBO_J_K,
  MY_COMBO_K_L,

  MY_COMBO_M_COMMA,
  MY_COMBO_COMMA_PERIOD,
};

const uint16_t PROGMEM w_e_combo[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM e_r_combo[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM r_t_combo[] = {KC_R, KC_T, COMBO_END};

const uint16_t PROGMEM s_d_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM d_f_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM f_g_combo[] = {KC_F, KC_G, COMBO_END};

const uint16_t PROGMEM x_c_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM c_v_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM v_b_combo[] = {KC_V, KC_B, COMBO_END};

const uint16_t PROGMEM u_i_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM i_o_combo[] = {KC_I, KC_O, COMBO_END};

const uint16_t PROGMEM j_k_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM k_l_combo[] = {KC_K, KC_L, COMBO_END};

const uint16_t PROGMEM m_comma_combo[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM comma_period_combo[] = {KC_COMMA, KC_DOT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [MY_COMBO_W_E] = COMBO(w_e_combo, KC_AT),
  [MY_COMBO_E_R] = COMBO(e_r_combo, KC_AMPR),
  [MY_COMBO_R_T] = COMBO(r_t_combo, KC_PIPE),

  [MY_COMBO_S_D] = COMBO(s_d_combo, KC_ASTR),
  [MY_COMBO_D_F] = COMBO(d_f_combo, KC_EQUAL),
  [MY_COMBO_F_G] = COMBO(f_g_combo, KC_DLR),

  [MY_COMBO_X_C] = COMBO(x_c_combo, KC_HASH),
  [MY_COMBO_C_V] = COMBO(c_v_combo, KC_EXLM),
  [MY_COMBO_V_B] = COMBO(v_b_combo, KC_CIRC),

  [MY_COMBO_U_I] = COMBO(u_i_combo, KC_LCBR),
  [MY_COMBO_I_O] = COMBO(i_o_combo, KC_RCBR),

  [MY_COMBO_J_K] = COMBO(j_k_combo, KC_LPRN),
  [MY_COMBO_K_L] = COMBO(k_l_combo, KC_RPRN),

  [MY_COMBO_M_COMMA] = COMBO(m_comma_combo, KC_LBRC),
  [MY_COMBO_COMMA_PERIOD] = COMBO(comma_period_combo, KC_RBRC),
};

#endif

#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0
  };

  oled_write_P(qmk_logo, false);
}

/* static void render_mods(void) { */
  /* int mods = get_mods(); */
  /* if (mods & MOD_BIT(KC_LCMD)) { */
    /* oled_write_P(PSTR("Cmd "), false); */
  /* } */
  /* if (mods & MOD_BIT(KC_LOPT)) { */
    /* oled_write_P(PSTR("Opt "), false); */
  /* } */
  /* if (mods & MOD_BIT(KC_LCTRL) || mods & MOD_BIT(KC_RCTRL)) { */
    /* oled_write_P(PSTR("Ctrl "), false); */
  /* } */
  /* if (mods & MOD_BIT(KC_LSFT) || mods & MOD_BIT(KC_RSFT)) { */
    /* oled_write_P(PSTR("Shft "), false); */
  /* } */
  /* oled_write_P(PSTR("\n"), false); */
/* } */

static void render_message(const char *message) {
  current_message = message;
  current_message_timer = timer_read32();
}

static void render_status(void) {
  /* oled_write_P(PSTR("\n"), false); */

  /* render_layer_name(); */
  /* render_mods(); */

#ifdef LEADER_ENABLE
  oled_advance_page(true);
  if (leader_mode) {
    oled_write_P(PSTR("Leading"), false);
  } else if (timer_elapsed32(current_message_timer) < CURRENT_MESSAGE_TIMEOUT) {
    oled_write_P(current_message, false);
  }
  oled_advance_page(true);
#endif
}

void render_status_bar(void) {
  uint8_t modifiers = get_mods();
  led_t led_state = host_keyboard_led_state();
  oled_write_P(PSTR("\325\326"), (modifiers & MOD_MASK_SHIFT));
  oled_write_P(PSTR("\327\330"), (modifiers & MOD_MASK_CTRL));
  oled_write_P(PSTR("\331\332"), (modifiers & MOD_MASK_ALT));
  oled_write_P(PSTR("\333\334"), (modifiers & MOD_MASK_GUI));
  oled_write_P(PSTR("         "), false);
  oled_write_P(PSTR("\235\236"), led_state.caps_lock);
  oled_write_P(PSTR("\275\276"), led_state.num_lock);
}

void render_primary_oled(void) {
  oled_set_cursor(0, 0);
  render_qmk_logo();
  render_status();
  oled_advance_page(true);
  oled_advance_page(true);
  render_status_bar();
}

void oled_task_user(void) {
  if (reset_timer) {
    handle_reset();
  } else {
    render_primary_oled();
  }
}

void swap_home_row_mod_layer_state(void) {
  if (get_highest_layer(layer_state) == _BASE_HRM) {
    layer_move(_BASE);
    set_single_persistent_default_layer(_BASE);
  } else {
    layer_move(_BASE_HRM);
    set_single_persistent_default_layer(_BASE_HRM);
  }
}

#ifdef LEADER_ENABLE

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leader_success = leading = false;

    SEQ_ONE_KEY(KC_M) {
      leader_success = true;
      swap_home_row_mod_layer_state();
    }
    SEQ_TWO_KEYS(KC_E, KC_U) {
      leader_success = true;
      SEND_STRING(":+1:");
    }
    SEQ_TWO_KEYS(KC_E, KC_D) {
      leader_success = true;
      SEND_STRING(":-1:");
    }
    SEQ_TWO_KEYS(KC_E, KC_O) {
      leader_success = true;
      SEND_STRING(":ok:");
    }
    SEQ_TWO_KEYS(KC_E, KC_P) {
      leader_success = true;
      SEND_STRING(":poop:");
    }
    SEQ_TWO_KEYS(KC_G, KC_A) {
      leader_success = true;
      layer_move(_GAME);
    }
    /* SEQ_THREE_KEYS(KC_M, KC_V, KC_G) { */
      /* leader_success = true; */
      /* SEND_STRING(""); */
    /* } */

    leader_end();
  }
}

void leader_start() {
  leader_mode = true;
}

void leader_end(void) {
  leader_mode = false;

  if (leader_success) {
    render_message(PSTR("Sequence Matched"));
  } else {
    render_message(PSTR("No Sequence Match"));
  }
}

#endif

#endif

bool process_record_user_for_side(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MY_RESET:
      reset_with_message();
      break;
    case KC_MPLY:
      render_message(PSTR("Play/Pause"));
      break;
    case KC_MNXT:
      render_message(PSTR("Next Track"));
      break;
    case KC_MPRV:
      render_message(PSTR("Previous Track"));
      break;
  }

  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return process_hrm_fix(keycode, record) &&
         process_record_user_for_side(keycode, record);
}

void matrix_init_user(void) {
  // I don't know why this is necessary, but without it, the default layer loaded from the
  // eeprom is applied, but no functions to check the layer return the correct values.
  layer_state_set(eeconfig_read_default_layer());
}

/* layer_state_t default_layer_state_set_user(layer_state_t state) { */
/* #ifdef RGBLIGHT_LAYERS */
/* #endif */
  /* return state; */
/* } */

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_LAYERS
  rgblight_set_layer_state(0, layer_state_cmp(state, _SYMNUM) || layer_state_cmp(state, _SYMNUM_HRM));
  rgblight_set_layer_state(1, layer_state_cmp(state, _NAV));
  rgblight_set_layer_state(2, layer_state_cmp(state, _FUNC));
  rgblight_set_layer_state(3, layer_state_cmp(state, _GAME));
  rgblight_set_layer_state(4, layer_state_cmp(state, _GAME_NUM));
  rgblight_set_layer_state(5, layer_state_cmp(state, _GAME_NUM_PAD));
#endif
  return state;
}

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

#include <stdio.h>
#include "../newing_primary/common.c"
#include "./icons.c"
#include "./bongo_cat.c"

#define SHOW_BONGO_CAT_WPM 90

bool showing_bongo_cat = false;
char wpm_str[20];
uint8_t max_wpm = 0;

#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

#define LAYER_INDICATOR_COL 1
#define LAYER_INDICATOR_ROW 2


static void render_icon(uint8_t column, uint8_t row, const char *icon) {
  for (uint8_t i = 0; i < 4; i++) {
    oled_set_cursor(column, row + i);
    oled_write_raw_P(icon + i * 32, 32);
  }
}

static void render_layer_indicator_icon(const char *icon) {
  render_icon(LAYER_INDICATOR_COL, LAYER_INDICATOR_ROW, icon);
}

static void render_layer_name(const char *text) {
  oled_set_cursor(8, 3);
  oled_write_P(text, false);
  oled_advance_page(true);
}

static void render_layer_image(void) {
  bool hrm = false;

  switch (get_highest_layer(layer_state)) {
    case _BASE:
      render_layer_indicator_icon(base_icon);
      render_layer_name(PSTR("Base"));
      break;
    case _BASE_HRM:
      render_layer_indicator_icon(base_icon);
      render_layer_name(PSTR("Base"));
      hrm = true;
      break;
    case _NAV:
      render_layer_indicator_icon(nav_icon);
      render_layer_name(PSTR("Move"));
      break;
    case _SYMNUM:
      render_layer_indicator_icon(symnum_icon);
      render_layer_name(PSTR("Symbols"));
      break;
    case _SYMNUM_HRM:
      render_layer_indicator_icon(symnum_icon);
      render_layer_name(PSTR("Symbols"));
      hrm = true;
      break;
    case _FUNC:
      render_layer_indicator_icon(func_icon);
      render_layer_name(PSTR("Function"));
      break;
    case _GAME:
      render_layer_indicator_icon(game_icon);
      render_layer_name(PSTR("Game"));
      break;
    case _GAME_NUM:
      render_layer_indicator_icon(game_icon);
      render_layer_name(PSTR("Game Numbers"));
      break;
    case _GAME_NUM_PAD:
      render_layer_indicator_icon(game_icon);
      render_layer_name(PSTR("Game Num Pad"));
      break;
    default:
      render_layer_name(PSTR("Unknown"));
  }

  oled_set_cursor(8, 5);
  if (hrm) {
    oled_write_P(PSTR("HRM enabled"), false);
  } else {
    oled_write_P(PSTR("           "), false);
  }
}

void render_secondary_oled(void) {
  bool should_show_bongo_cat = get_current_wpm() > 80;

  if ((showing_bongo_cat && !should_show_bongo_cat) || (!showing_bongo_cat && should_show_bongo_cat)) {
    max_wpm = 0;
    oled_set_cursor(0, 0);
    oled_clear();
    oled_render();
  }

  showing_bongo_cat = should_show_bongo_cat;


  if (showing_bongo_cat) {
    oled_set_cursor(0, 1);
    uint8_t wpm = get_current_wpm();
    if (wpm > max_wpm) {
      max_wpm = wpm;
    }

    render_bongo_cat();
    oled_set_cursor(0, 7);

    sprintf(wpm_str, " WPM:%-3d Max:%-3d", wpm, max_wpm);
    oled_write(wpm_str, false);
  } else {
    oled_set_cursor(0, 0);
    render_layer_image();
  }
}

void oled_task_user(void) {
  if (reset_timer) {
    handle_reset();
  } else {
    render_secondary_oled();
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MY_RESET:
      reset_with_message();
      break;
  }

  return true;
}

#endif

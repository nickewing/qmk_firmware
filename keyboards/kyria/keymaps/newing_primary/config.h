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

#pragma once

#define EE_HANDS

#define TAPPING_TERM 200
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_FORCE_HOLD

#define MOUSEKEY_DELAY 100
#define MOUSEKEY_INTERVAL 10
#define MOUSEKEY_MAX_SPEED 3
#define MOUSEKEY_TIME_TO_MAX 30

// #define SPLIT_MODS_ENABLE
#define SPLIT_LAYER_STATE_ENABLE

#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
  #define OLED_FONT_H "users/cjuniet/glcdfont.c"
#endif

#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_SLEEP
  // #define RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_EFFECT_BREATHING
  // #define RGBLIGHT_EFFECT_KNIGHT
  // #define RGBLIGHT_EFFECT_STATIC_GRADIENT
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 150

  #define RGBLIGHT_LAYERS
  #define RGBLIGHT_MAX_LAYERS 16
#endif

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK

#ifdef COMBO_ENABLE
  #define COMBO_COUNT 15
  #define COMBO_TERM 20
#endif

#ifdef LEADER_ENABLE
  #define LEADER_PER_KEY_TIMING
  #define LEADER_TIMEOUT 350
#endif

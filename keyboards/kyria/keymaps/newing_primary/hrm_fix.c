// See: https://github.com/qmk/qmk_firmware/issues/642
// and quantum/process_keycode/process_space_cadet.c

static uint8_t  hrmf_lprn_last  = 0;
static uint16_t hrmf_lprn_timer = 0;

static uint8_t  hrmf_rprn_last  = 0;
static uint16_t hrmf_rprn_timer = 0;

static uint8_t  hrmf_astr_last  = 0;
static uint16_t hrmf_astr_timer = 0;

void perform_hrm_fix(keyrecord_t *record,
                     uint16_t hrmf_keycode,
                     uint8_t *last,
                     uint16_t *timer,
                     uint8_t hold_mod,
                     uint8_t tap_mod,
                     uint8_t keycode) {

  if (record->event.pressed) {
    *last  = hold_mod;
    *timer = timer_read();

    if (IS_MOD(hold_mod)) {
      register_mods(MOD_BIT(hold_mod));
    }
  } else {
#ifdef TAPPING_TERM_PER_KEY
    if (*last == hold_mod && timer_elapsed(*timer) < get_tapping_term(hrmf_keycode, record)) {
#else
    if (*last == hold_mod && timer_elapsed(*timer) < TAPPING_TERM) {
#endif
      if (hold_mod != tap_mod) {
        if (IS_MOD(hold_mod)) {
          unregister_mods(MOD_BIT(hold_mod));
        }
        if (IS_MOD(tap_mod)) {
          register_mods(MOD_BIT(tap_mod));
        }
      }
      tap_code(keycode);
      if (IS_MOD(tap_mod)) {
        unregister_mods(MOD_BIT(tap_mod));
      }
    } else {
      if (IS_MOD(hold_mod)) {
        unregister_mods(MOD_BIT(hold_mod));
      }
    }
  }
}

bool process_hrm_fix(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case HRMF_LSFT_LPRN:
      perform_hrm_fix(record, keycode, &hrmf_lprn_last, &hrmf_lprn_timer, KC_LSFT, KC_LSFT, KC_9);
      return false;
    case HRMF_LCMD_RPRN:
      perform_hrm_fix(record, keycode, &hrmf_rprn_last, &hrmf_rprn_timer, KC_LCMD, KC_LSFT, KC_0);
      return false;
    case HRMF_LOPT_ASTR:
      perform_hrm_fix(record, keycode, &hrmf_astr_last, &hrmf_astr_timer, KC_LOPT, KC_LSFT, KC_8);
      return false;
    default:
      if (record->event.pressed) {
        hrmf_lprn_last = 0;
        hrmf_rprn_last = 0;
        hrmf_astr_last = 0;
      }
      break;
  }
  return true;
}

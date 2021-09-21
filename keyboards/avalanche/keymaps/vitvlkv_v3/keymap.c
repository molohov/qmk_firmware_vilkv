#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    // _ADJUST,
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    // ADJUST,
};

#define MT_LALT LALT_T(KC_ESC)
#define MT_RALT RALT_T(KC_ENT)
#define MT_SPC LT(_RAISE, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
                 KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                                       KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
                 KC_BSLS, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
        KC_LGUI, KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_RGUI,
                 KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_CAPS, XXXXXXX, KC_PSCR,  KC_CAPS,KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RCTL,
                                            KC__MUTE,KC_GRV,  KC_LSFT, MT_SPC,  MT_LALT, MT_RALT,  MO(_LOWER),KC_RSFT,KC_RBRC,KC_INS
    ),
    [_LOWER] = LAYOUT(
                 XXXXXXX, XXXXXXX, XXXXXXX, KC_PLUS, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                 _______, XXXXXXX, KC_LBRC, KC_EQL,  KC_RBRC, XXXXXXX,                                     XXXXXXX, KC_HOME, KC_UP,   KC_END,  XXXXXXX, XXXXXXX,
        XXXXXXX, _______, XXXXXXX, KC_LPRN, KC_MINS, KC_RPRN, KC_DEL,                                      KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, XXXXXXX,
                 _______, XXXXXXX, KC_LCBR, KC_UNDS, KC_RCBR, XXXXXXX, _______, _______, _______, _______, XXXXXXX, KC_PGUP, KC_APP,  KC_PGDN, XXXXXXX, _______,
                                            _______, XXXXXXX, _______, _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX
    ),
    [_RAISE] = LAYOUT(
                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, KC_PCMM, XXXXXXX, XXXXXXX, XXXXXXX,
                 _______, XXXXXXX, KC_EXLM, KC_AT,   KC_HASH, XXXXXXX,                                     KC_0,    KC_1,    KC_2,    KC_3,    XXXXXXX, XXXXXXX,
        XXXXXXX, _______, XXXXXXX, KC_DLR,  KC_PERC, KC_CIRC, KC_DEL,                                      KC_BSPC, KC_4,    KC_5,    KC_6,    XXXXXXX, XXXXXXX, XXXXXXX,
                 _______, XXXXXXX, KC_AMPR, KC_ASTR, KC_PCMM, XXXXXXX, _______, _______, _______, _______, XXXXXXX, KC_7,    KC_8,    KC_9,    KC_0,    _______,
                                            _______, XXXXXXX, _______, _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX
    ),
    // [_ADJUST] = LAYOUT(
    //              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, KC_PCMM, XXXXXXX, XXXXXXX, XXXXXXX,
    //              KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC,                                     KC_AMPR, KC_ASTR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //     XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    //              _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    //                                         _______, XXXXXXX, _______, _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX
    // ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC__VOLUP);
        } else {
            tap_code(KC__VOLDOWN);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_PGUP);
        } else {
            tap_code(KC_PGDOWN);
        }
    }
    return true;
}

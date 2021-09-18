#include QMK_KEYBOARD_H

enum layer {
    LAYER_0,
    LAYER_1,
    LAYER_2,
};

#define FN_1 MO(LAYER_1)
#define MT_GRV LT(LAYER_2, KC_GRV)
#define MT_LALT LALT_T(KC_LGUI)
#define MT_RALT RALT_T(KC_ENT)
#define MT_SPC LT(LAYER_2, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_0] = LAYOUT(
                 KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                                       KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
                 KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        XXXXXXX, KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, XXXXXXX,
                 KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_DEL,  KC_APP,  KC_PSCR,  KC_BSPC,KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RCTL,
                                            KC__MUTE,MT_GRV,  KC_LSFT, MT_SPC,  MT_LALT, MT_RALT,  FN_1,   KC_RSFT, KC_TILD, KC_INS
    ),
    [LAYER_1] = LAYOUT(
                 _______, XXXXXXX, XXXXXXX, KC_EQL,  XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                 _______, XXXXXXX, KC_LPRN, KC_PLUS, KC_RPRN, XXXXXXX,                                     XXXXXXX, KC_HOME, KC_UP,   KC_END,  XXXXXXX, XXXXXXX,
        _______, _______, XXXXXXX, KC_LBRC, KC_MINS, KC_RBRC, KC_DEL,                                      KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, XXXXXXX,
                 _______, XXXXXXX, KC_LCBR, KC_UNDS, KC_RCBR, XXXXXXX, _______, _______, _______, _______, XXXXXXX, KC_PGUP, KC_PGDN, XXXXXXX, XXXXXXX, _______,
                                            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [LAYER_2] = LAYOUT(
                 _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, KC_DOT,  KC_0,    KC_COMM, XXXXXXX, XXXXXXX,
                 _______, XXXXXXX, KC_EXLM, KC_AT,   KC_HASH, XXXXXXX,                                     XXXXXXX, KC_1,    KC_2,    KC_3,    XXXXXXX, XXXXXXX,
        _______, _______, XXXXXXX, KC_DLR,  KC_PERC, KC_CIRC, KC_DEL,                                      KC_BSPC, KC_4,    KC_5,    KC_6,    XXXXXXX, XXXXXXX, XXXXXXX,
                 _______, XXXXXXX, KC_AMPR, KC_ASTR, XXXXXXX, XXXXXXX, _______, _______, _______, _______, XXXXXXX, KC_7,    KC_8,    KC_9,    XXXXXXX, _______,
                                            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
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

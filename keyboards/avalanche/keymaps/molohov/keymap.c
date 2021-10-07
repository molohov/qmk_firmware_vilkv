
/*
qmk compile -kb avalanche/rev2 -km default_rev2
qmk flash -kb avalanche/rev2 -km default_rev2
*/

#include QMK_KEYBOARD_H

enum layer {
    _HANDS_DOWN,
    _BYOBU_NAV,
    _RAISE,
    _QWERTY,
    _ADJUST,
    _NUMROW,
};

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum custom_keycodes {
    KC_HANDS_DOWN = SAFE_RANGE,
    KC_QWERTY,
    KC_BYOBU_NAV,
    KC_RAISE,
    KC_ADJUST,
    KC_NUMROW,
};

#define MINSNUM LT(_NUMROW, KC_MINS)
#define ENTNUM LT(_NUMROW, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Layer: HANDS_DOWN
 *                                     ╭────────╮                                                                         ╭────────╮
 *                            ╭────────╯   #    ╰────────╮                                                       ╭────────╯    *   ╰────────╮
 *                            │   @    │   3    │   $    ╰────────╮                                     ╭────────╯    &   │    8   │    (   │
 *          ╭────────╮────────╯   2    ╰────────╯   4    │   %    │                                     │    ^   │    7   ╰────────╯    9   ╰────────╭────────╮
 *          │        │   !    ╰────────╯        ╰────────╯   5    │                                     │    6   ╰────────╯        ╰────────╯    )   │    _   │
 *          │  Esc   │   1    │        │   E    │        ╰────────╯                                     ╰────────╯        │    I   │        │    0   │   -    │
 *          ╰────────╯────────╯   W    ╰────────╯   R    │        │                                     │        │    U   ╰────────╯    O   ╰────────╰────────╯
 *          │        │        ╰────────╯        ╰────────╯   T    │                                     │    Y   ╰────────╯        ╰────────╯        │        │
 *          │  Tab   │   Q    │        │   D    │        ╰────────╯ ╭────────╮               ╭────────╮ ╰────────╯        │    K   │        │    P   │ Bkspce │
 * ╭────────╯────────╯────────╯   S    ╰────────╯   F    │        │ │        │               │        │ │        │    J   ╰────────╯    L   ╰────────╰────────╰────────╮
 * │  ` ~   │  Esc   │        ╰────────╯        ╰────────╯   G    │ │   {    │               │    }   │ │    H   ╰────────╯    <   ╰────────╯    :   │    "   │   |    │
 * │ (c/a/g)│ (ctrl) │   A    │        │   C    │        ╰────────╯ ╰────────╯               ╰────────╯ ╰────────╯        │    ,   │    >   │    ;   │    '   │   \    │
 * ╰────────╮────────╯────────╯   X    ╰────────╯   V    │        │  ╭────────╮             ╭────────╮  │        │    M   ╰────────╯    .   ╰────────╰────────╭────────╯
 *          │        │        ╰────────╯        ╰────────╯   B    │  │        │             │    +   │  │    N   ╰────────╯        ╰────────╯    ?   │(rShift)│
 *          │ Shift  │   Z    │                ╭────────╮╰────────╯  │ Bkspce │             │   =    │  ╰────────╯╭────────╮                │    /   │ Enter  │
 *          ╰────────╯────────╯      ╭────────╮│        ╰────────╮   ╰────────╯             ╰────────╯   ╭────────╯        │╭────────╮      ╰────────╰────────╯
 *                                   │ Paste  ││  CMD   │        ╰────────╮                     ╭────────╯        │  ALT   ││        │
 *                                   │ Board  │╰────────╯  RSE   │        ╰────────╮   ╭────────╯        │  LWR   ╰────────╯│  Mute  │
 *                                   ╰─encodr─╯         ╰────────╯ Bkspace│        │   │        │ Space  ╰────────╯         ╰─encodr─╯
 *                                                               ╰────────╯  Tab   │   │ Enter  ╰────────╯
 *                                                                        ╰────────╯   ╰────────╯
 */
    [_HANDS_DOWN] = LAYOUT(
                 KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
                 KC_EQL,  KC_X,    KC_F,    KC_M,    KC_P,    KC_B,                                  KC_MINS, KC_SLSH, KC_DOT,  KC_COMM, KC_J,    KC_BSLS,
 LCAG_T(KC_GRV), KC_Z,    KC_R,    KC_S,    KC_N,    KC_T,    KC_G,    KC_LCBR,             KC_RCBR, KC_QUOT, KC_A,    KC_E,    KC_I,    KC_H,    KC_Q, KC_BSLS,
                 KC_HOME, KC_W,    KC_C,    KC_L,    KC_D,    KC_V,    KC_BSPC,             KC_EQL,  KC_SCLN, KC_U,    KC_O,    KC_Y,    KC_K,    KC_END,
                                   XXXXXXX,  KC_ADJUST, KC_RAISE,LSFT_T(KC_BSPC), KC_TAB,              KC_ENT, KC_SPC,  KC_BYOBU_NAV,KC_NUMROW, KC_MUTE
    ),

/*
 * Layer: BYOBU_NAV
 *                                     ╭────────╮                                                                         ╭────────╮
 *                            ╭────────╯        ╰────────╮                                                       ╭────────╯        ╰────────╮
 *                            │        │   F3   │        ╰────────╮                                     ╭────────╯        │   F8   │        │
 *          ╭────────╮────────╯   F2   ╰────────╯   F4   │        │                                     │        │   F7   ╰────────╯   F9   ╰────────╭────────╮
 *          │        │        ╰────────╯        ╰────────╯   F5   │                                     │   F6   ╰────────╯        ╰────────╯        │        │
 *          │  IMP   │   F1   │        │   #    │        ╰────────╯                                     ╰────────╯        │   *    │        │  F10   │  F11   │
 *          ╰────────╯────────╯   @    ╰────────╯   $    │        │                                     │        │   &    ╰────────╯   (    ╰────────╰────────╯
 *          │        │        ╰────────╯        ╰────────╯   %    │                                     │   ^    ╰────────╯        ╰────────╯        │        │
 *          │  Tab   │   !    │  Save  │   (    │        ╰────────╯ ╭────────╮               ╭────────╮ ╰────────╯        │        │        │    )   │ Bckspc │
 * ╭────────╯────────╯────────╯  4Web  ╰────────╯   )    │        │ │   {    │               │    }   │ │        │        ╰────────╯        ╰────────╰────────╰────────╮
 * │        │        │        ╰────────╯        ╰────────╯        │ │   [    │               │    ]   │ │        ╰────────╯    <   ╰────────╯    :   │    "   │        │
 * │ MEDIAQ │  Ctrl  │        │        │   {    │        ╰────────╯ ╰─encodr─╯               ╰─encodr─╯ ╰────────╯        │    ,   │    >   │    ;   │    '   │  F12   │
 * ╰────────╮────────╯────────╯        ╰────────╯   }    │        │  ╭────────╮             ╭────────╮  │        │        ╰────────╯    .   ╰────────╰────────╭────────╯
 *          │        │        ╰────────╯        ╰────────╯        │  │        │             │    +   │  │        ╰────────╯        ╰────────╯    ?   │(rShift)│
 *          │ Shift  │        │                ╭────────╮╰────────╯  │ Bckspc │             │    =   │  ╰────────╯╭────────╮                │    /   │  Enter │
 *          ╰────────╯────────╯      ╭────────╮│        ╰────────╮   ╰────────╯             ╰────────╯   ╭────────╯        │╭────────╮      ╰────────╰────────╯
 *                                   │        ││  FONT  │        ╰────────╮                     ╭────────╯        │  Alt   ││        │
 *                                   │        │╰────────╯  RSE   │        ╰────────╮   ╭────────╯        │  LWR   ╰────────╯│  Mute  │
 *                                   ╰────────╯         ╰────────╯ Space  │        │   │    _   │  Space ╰────────╯         ╰────────╯
 *                                                               ╰────────╯ Enter  │   │   -    ╰────────╯
 *                                                                        ╰────────╯   ╰────────╯
 */
    [_BYOBU_NAV] = LAYOUT(
                 XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                 KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
                 _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                               KC_CIRC, KC_AMPR, KC_UP,   KC_PGUP, KC_PGDN, _______,
        XXXXXXX, _______, XXXXXXX, XXXXXXX, KC_LPRN, KC_RPRN, XXXXXXX, KC_LBRC,             KC_RBRC, XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, KC_F12,
                 _______, XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX, _______,             _______, KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F8,   KC_F6,
                                   XXXXXXX, XXXXXXX, _______, _______, _______,             _______, _______, _______, _______, _______
    ),

/*
 * Layer: RAISE
 *                                     ╭────────╮                                                                         ╭────────╮
 *                            ╭────────╯        ╰────────╮                                                       ╭────────╯        ╰────────╮
 *                            │        │        │        ╰────────╮                                     ╭────────╯        │        │        │
 *          ╭────────╮────────╯        ╰────────╯        │        │                                     │        │        ╰────────╯        ╰────────╭────────╮
 *          │        │        ╰────────╯ Mouse  ╰────────╯        │                                     │        ╰────────╯        ╰────────╯        │        │
 *          │  UNDO  │  REDO  │        │  Up    │        ╰────────╯                                     ╰────────╯  Prev  │   Up   │  Next  │        │        │
 *          ╰────────╯────────╯        ╰────────╯        │        │                                     │        │  Word  ╰────────╯  Word  ╰────────╰────────╯
 *          │ Shift+ │        ╰────────╯ Mouse  ╰────────╯        │                                     │        ╰────────╯        ╰────────╯        │        │
 *          │  Tab   │        │ Mouse  │ Down   │ Mouse  ╰────────╯ ╭────────╮               ╭────────╮ ╰────────╯        │  Down  │        │        │        │
 * ╭────────╯────────╯────────╯ Left   ╰────────╯ Rght   │        │ │   {    │               │    }   │ │        │  Left  ╰────────╯  Rght  ╰────────╰────────╰────────╮
 * │  ` ~   │ (Ctrl) │        ╰────────╯        ╰────────╯        │ │   [    │               │    ]   │ │        ╰────────╯        ╰────────╯        │        │        │
 * │(c/a/g) │ CAPS   │        │        │        │        ╰────────╯ ╰─encodr─╯               ╰─encodr─╯ ╰────────╯  Line  │        │  Line  │        │        │        │
 * ╰────────╮────────╯────────╯        ╰────────╯        │        │  ╭────────╮             ╭────────╮  │        │  Strt  ╰────────╯  End   ╰────────╰────────╭────────╯
 *          │        │        ╰────────╯        ╰────────╯        │  │        │             │        │  │        ╰────────╯        ╰────────╯        │        │
 *          │ Shift  │        │                ╭────────╮╰────────╯  │        │             │        │  ╰────────╯╭────────╮                │        │        │
 *          ╰────────╯────────╯      ╭────────╮│        ╰────────╮   ╰────────╯             ╰────────╯   ╭────────╯        │╭────────╮      ╰────────╰────────╯
 *                                   │ paste  ││  Cmd   │        ╰────────╮                     ╭────────╯        │  Alt   ││        │
 *                                   │ board  │╰────────╯  RSE   │        ╰────────╮   ╭────────╯  Rght  │  LWR   ╰────────╯│  Mute  │
 *                                   ╰────────╯         ╰────────╯ Space  │        │   │  Left  │  Clck  ╰────────╯         ╰────────╯
 *                                                               ╰────────╯ Enter  │   │  Clck  ╰────────╯
 *                                                                        ╰────────╯   ╰────────╯
 */
    [_RAISE] = LAYOUT(
                 KC_UNDO, XXXXXXX, _______, _______, _______, _______,                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                 XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX,                               XXXXXXX, XXXXXXX,KC_UP,   XXXXXXX,KC_PLUS, KC_DEL,
_______, LCTL_T(KC_CAPS), XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, KC_LBRC,             KC_RBRC, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, XXXXXXX,
                 _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   _______, _______, _______, _______, _______,             KC_BTN1, KC_BTN2, _______, _______, _______
    ),

/*
 * Layer: QWERTY
 *                                     ╭────────╮                                                                         ╭────────╮
 *                            ╭────────╯   #    ╰────────╮                                                       ╭────────╯    *   ╰────────╮
 *                            │   @    │   3    │   $    ╰────────╮                                     ╭────────╯    &   │    8   │    (   │
 *          ╭────────╮────────╯   2    ╰────────╯   4    │   %    │                                     │    ^   │    7   ╰────────╯    9   ╰────────╭────────╮
 *          │        │   !    ╰────────╯        ╰────────╯   5    │                                     │    6   ╰────────╯        ╰────────╯    )   │    _   │
 *          │  Esc   │   1    │        │   E    │        ╰────────╯                                     ╰────────╯        │    I   │        │    0   │   -    │
 *          ╰────────╯────────╯   W    ╰────────╯   R    │        │                                     │        │    U   ╰────────╯    O   ╰────────╰────────╯
 *          │        │        ╰────────╯        ╰────────╯   T    │                                     │    Y   ╰────────╯        ╰────────╯        │        │
 *          │  Tab   │   Q    │        │   D    │        ╰────────╯ ╭────────╮               ╭────────╮ ╰────────╯        │    K   │        │    P   │ Bkspce │
 * ╭────────╯────────╯────────╯   S    ╰────────╯   F    │        │ │        │               │        │ │        │    J   ╰────────╯    L   ╰────────╰────────╰────────╮
 * │  ` ~   │  Esc   │        ╰────────╯        ╰────────╯   G    │ │   {    │               │    }   │ │    H   ╰────────╯    <   ╰────────╯    :   │    "   │   |    │
 * │ (c/a/g)│ (ctrl) │   A    │        │   C    │        ╰────────╯ ╰────────╯               ╰────────╯ ╰────────╯        │    ,   │    >   │    ;   │    '   │   \    │
 * ╰────────╮────────╯────────╯   X    ╰────────╯   V    │        │  ╭────────╮             ╭────────╮  │        │    M   ╰────────╯    .   ╰────────╰────────╭────────╯
 *          │        │        ╰────────╯        ╰────────╯   B    │  │        │             │    +   │  │    N   ╰────────╯        ╰────────╯    ?   │(rShift)│
 *          │ Shift  │   Z    │                ╭────────╮╰────────╯  │ Bkspce │             │   =    │  ╰────────╯╭────────╮                │    /   │ Enter  │
 *          ╰────────╯────────╯      ╭────────╮│        ╰────────╮   ╰────────╯             ╰────────╯   ╭────────╯        │╭────────╮      ╰────────╰────────╯
 *                                   │ Paste  ││  CMD   │        ╰────────╮                     ╭────────╯        │  ALT   ││        │
 *                                   │ Board  │╰────────╯  RSE   │        ╰────────╮   ╭────────╯        │  LWR   ╰────────╯│  Mute  │
 *                                   ╰─encodr─╯         ╰────────╯ Bkspace│        │   │        │ Space  ╰────────╯         ╰─encodr─╯
 *                                                               ╰────────╯  Tab   │   │ Enter  ╰────────╯
 *                                                                        ╰────────╯   ╰────────╯
 */
    [_QWERTY] = LAYOUT(
                 KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
                 KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
 LCAG_T(KC_GRV), KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LCBR,             KC_RCBR, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS,
                 KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_BSPC,             KC_EQL,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT),
                                   XXXXXXX,  KC_ADJUST, KC_RAISE,LSFT_T(KC_BSPC), KC_TAB,              KC_ENT, KC_SPC,  KC_BYOBU_NAV,KC_NUMROW, KC_MUTE
    ),
/*
 * Layer: ADJUST
 *                                     ╭────────╮                                                                         ╭────────╮
 *                            ╭────────╯  RGB   ╰────────╮                                                       ╭────────╯  RGB   ╰────────╮
 *                            │        │  HUE-  │  RGB   ╰────────╮                                     ╭────────╯  RGB   │  HUE+  │        │
 *          ╭────────╮────────╯        ╰────────╯  SAT-  │  RGB   │                                     │  RGB   │  SAT+  ╰────────╯        ╰────────╭────────╮
 *          │        │        ╰────────╯        ╰────────╯  VAL-  │                                     │  VAL+  ╰────────╯        ╰────────╯        │        │
 *          │        │        │        │        │        ╰────────╯                                     ╰────────╯        │        │        │        │        │
 *          ╰────────╯────────╯        ╰────────╯        │        │                                     │        │        ╰────────╯        ╰────────╰────────╯
 *          │        │        ╰────────╯        ╰────────╯        │                                     │        ╰────────╯        ╰────────╯        │        │
 *          │        │        │        │        │        ╰────────╯ ╭────────╮               ╭────────╮ ╰────────╯        │        │        │        │        │
 * ╭────────╯────────╯────────╯        ╰────────╯        │        │ │  RGB   │               │  RGB   │ │        │        ╰────────╯        ╰────────╰────────╰────────╮
 * │ RGB    │        │        ╰────────╯        ╰────────╯        │ │  I/O   │               │  I/O   │ │        ╰────────╯        ╰────────╯        │        │  RGB   │
 * │ RMOD   │        │        │        │        │        ╰────────╯ ╰─encodr─╯               ╰─encodr─╯ ╰────────╯        │        │        │        │        │  MOD   │
 * ╰────────╮────────╯────────╯        ╰────────╯        │        │  ╭────────╮             ╭────────╮  │        │        ╰────────╯        ╰────────╰────────╭────────╯
 *          │        │        ╰────────╯        ╰────────╯        │  │  RGB   │             │  RGB   │  │        ╰────────╯        ╰────────╯        │        │
 *          │        │        │                ╭────────╮╰────────╯  │  MOD-  │             │  MOD+  │  ╰────────╯╭────────╮                │        │        │
 *          ╰────────╯────────╯      ╭────────╮│        ╰────────╮   ╰────────╯             ╰────────╯   ╭────────╯        │╭────────╮      ╰────────╰────────╯
 *                                   │        ││        │        ╰────────╮                     ╭────────╯        │        ││        │
 *                                   │        │╰────────╯  RSE   │        ╰────────╮   ╭────────╯        │  LWR   ╰────────╯│        │
 *                                   ╰────────╯         ╰────────╯        │        │   │        │        ╰────────╯         ╰────────╯
 *                                                               ╰────────╯        │   │        ╰────────╯
 *                                                                        ╰────────╯   ╰────────╯
 */

    [_ADJUST] = LAYOUT(
                 XXXXXXX, XXXXXXX, XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD,                               RGB_VAI, RGB_SAI, RGB_HUI, XXXXXXX, XXXXXXX, XXXXXXX,
                 XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_RMOD,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,             RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD,
                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_RMOD,            RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   _______, _______, XXXXXXX, _______, _______,             _______, _______, XXXXXXX, _______, _______
    ),

/*
 * Layer: NUMROW
 *                                     ╭────────╮                                                                         ╭────────╮
 *                            ╭────────╯        ╰────────╮                                                       ╭────────╯        ╰────────╮
 *                            │        │        │        ╰────────╮                                     ╭────────╯        │        │        │
 *          ╭────────╮────────╯        ╰────────╯        │        │                                     │        │        ╰────────╯        ╰────────╭────────╮
 *          │        │        ╰────────╯        ╰────────╯        │                                     │        ╰────────╯        ╰────────╯        │        │
 *          │        │        │        │        │        ╰────────╯                                     ╰────────╯        │        │        │        │        │
 *          ╰────────╯────────╯        ╰────────╯        │        │                                     │        │        ╰────────╯        ╰────────╰────────╯
 *          │        │        ╰────────╯        ╰────────╯        │                                     │        ╰────────╯        ╰────────╯        │        │
 *          │        │        │        │        │        ╰────────╯ ╭────────╮               ╭────────╮ ╰────────╯        │        │        │        │        │
 * ╭────────╯────────╯────────╯        ╰────────╯        │        │ │        │               │        │ │        │        ╰────────╯        ╰────────╰────────╰────────╮
 * │        │        │        ╰────────╯        ╰────────╯        │ │        │               │        │ │        ╰────────╯        ╰────────╯        │        │        │
 * │        │        │        │        │        │        ╰────────╯ ╰─encodr─╯               ╰─encodr─╯ ╰────────╯        │        │        │        │        │        │
 * ╰────────╮────────╯────────╯        ╰────────╯        │        │  ╭────────╮             ╭────────╮  │        │        ╰────────╯        ╰────────╰────────╭────────╯
 *          │        │        ╰────────╯        ╰────────╯        │  │        │             │        │  │        ╰────────╯        ╰────────╯        │        │
 *          │        │        │                ╭────────╮╰────────╯  │        │             │        │  ╰────────╯╭────────╮                │        │        │
 *          ╰────────╯────────╯      ╭────────╮│        ╰────────╮   ╰────────╯             ╰────────╯   ╭────────╯        │╭────────╮      ╰────────╰────────╯
 *                                   │        ││        │        ╰────────╮                     ╭────────╯        │        ││        │
 *                                   │        │╰────────╯        │        ╰────────╮   ╭────────╯        │        ╰────────╯│        │
 *                                   ╰────────╯         ╰────────╯        │        │   │        │        ╰────────╯         ╰────────╯
 *                                                               ╰────────╯        │   │        ╰────────╯
 *                                                                        ╰────────╯   ╰────────╯
 */

        [_NUMROW] = LAYOUT(
                _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                XXXXXXX, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        XXXXXXX,XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,             _______, XXXXXXX, KC_4,    KC_5,    KC_6,    XXXXXXX, _______, _______,
                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_COMM, KC_DOT,  _______,             _______, XXXXXXX, KC_1,    KC_2,    KC_3,    KC_COMM, KC_DOT,
                                  _______, _______, _______, _______, _______,             _______, _______, KC_0,    _______, _______
        ),

/*
 * Base Layer: SAMPLE
 *                                     ╭────────╮                                                                         ╭────────╮
 *                            ╭────────╯        ╰────────╮                                                       ╭────────╯        ╰────────╮
 *                            │        │        │        ╰────────╮                                     ╭────────╯        │        │        │
 *          ╭────────╮────────╯        ╰────────╯        │        │                                     │        │        ╰────────╯        ╰────────╭────────╮
 *          │        │        ╰────────╯        ╰────────╯        │                                     │        ╰────────╯        ╰────────╯        │        │
 *          │        │        │        │        │        ╰────────╯                                     ╰────────╯        │        │        │        │        │
 *          ╰────────╯────────╯        ╰────────╯        │        │                                     │        │        ╰────────╯        ╰────────╰────────╯
 *          │        │        ╰────────╯        ╰────────╯        │                                     │        ╰────────╯        ╰────────╯        │        │
 *          │        │        │        │        │        ╰────────╯ ╭────────╮               ╭────────╮ ╰────────╯        │        │        │        │        │
 * ╭────────╯────────╯────────╯        ╰────────╯        │        │ │        │               │        │ │        │        ╰────────╯        ╰────────╰────────╰────────╮
 * │        │        │        ╰────────╯        ╰────────╯        │ │        │               │        │ │        ╰────────╯        ╰────────╯        │        │        │
 * │        │        │        │        │        │        ╰────────╯ ╰─encodr─╯               ╰─encodr─╯ ╰────────╯        │        │        │        │        │        │
 * ╰────────╮────────╯────────╯        ╰────────╯        │        │  ╭────────╮             ╭────────╮  │        │        ╰────────╯        ╰────────╰────────╭────────╯
 *          │        │        ╰────────╯        ╰────────╯        │  │        │             │        │  │        ╰────────╯        ╰────────╯        │        │
 *          │        │        │                ╭────────╮╰────────╯  │        │             │        │  ╰────────╯╭────────╮                │        │        │
 *          ╰────────╯────────╯      ╭────────╮│        ╰────────╮   ╰────────╯             ╰────────╯   ╭────────╯        │╭────────╮      ╰────────╰────────╯
 *                                   │        ││        │        ╰────────╮                     ╭────────╯        │        ││        │
 *                                   │        │╰────────╯        │        ╰────────╮   ╭────────╯        │        ╰────────╯│        │
 *                                   ╰────────╯         ╰────────╯        │        │   │        │        ╰────────╯         ╰────────╯
 *                                                               ╰────────╯        │   │        ╰────────╯
 *                                                                        ╰────────╯   ╰────────╯
 * [_SAMPLE] = LAYOUT(
 *         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
 *         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
 * XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
 *         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
 *                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
 * ),
 */
};


#ifdef OLED_ENABLE

static void render_logo(void) {

    static const char PROGMEM gimli_logo[] = {
        // 'gimli-logo', 128x32px
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf8, 0xf8, 0x7c, 0x7c, 0x3c, 0x3c, 0x3c, 0x3c,
        0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x1c, 0x1c, 0x0c, 0x0c, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x0f, 0x8f, 0x8f, 0xcf, 0xc6,
        0x02, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x0f, 0x8f, 0x8f, 0xcf, 0xc6, 0x02, 0x00,
        0x18, 0x18, 0xb8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x78, 0xfc, 0xfe, 0xfe, 0xff,
        0xff, 0xff, 0xff, 0xff, 0x7f, 0x7b, 0xf9, 0xf9, 0xf9, 0xf8, 0xf8, 0x78, 0xb8, 0x98, 0x18, 0x08,
        0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
        0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0xf8, 0xf8, 0xfc, 0x7e, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff,
        0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7e, 0xfc, 0xf8, 0xf8, 0xf0,
        0xf0, 0xf8, 0xf8, 0xfc, 0x7e, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00,
        0x00, 0x00, 0xf0, 0xf0, 0xf8, 0xf8, 0x7c, 0x7e, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x01, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x0f, 0x3f, 0x7f, 0x7f,
        0xff, 0xff, 0xff, 0xf7, 0xe7, 0xe7, 0xc7, 0x87, 0x87, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x06, 0x07, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0x00, 0x00, 0x00, 0x00, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01, 0x01,
        0x01, 0x01, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0xf8, 0xf8, 0x7c, 0x7e, 0x3e, 0x3f, 0x1f, 0x0f, 0x00,
        0x00, 0x00, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x03, 0x03, 0x07, 0x07, 0x0f, 0x0f, 0x1f, 0x3f, 0x3e, 0x3e, 0x3c, 0x3c, 0x3c,
        0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x3f,
        0x1f, 0x1f, 0x0f, 0x07, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x00, 0x00
    };

    oled_write_raw_P(gimli_logo, sizeof(gimli_logo));
}

static void render_face(void) {

    static const char PROGMEM gimli_face[] = {
        // 'gimli-face', 32x72px
0x3f, 0x3f, 0x1f, 0x1f, 0x8f, 0x8f, 0xcf, 0xc7, 0xc7, 0xc7, 0xc7, 0x01, 0x00, 0x00, 0xf8, 0xf8,
0xf8, 0x00, 0x01, 0x41, 0xe7, 0xc7, 0xc7, 0xc7, 0xc7, 0x8f, 0x8f, 0x1f, 0x1f, 0x3f, 0x7f, 0x7f,
0x1e, 0x1e, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0x00, 0x80, 0x30, 0x09, 0x01,
0x09, 0x30, 0x80, 0x00, 0x1f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3e, 0x1e, 0x1c,
0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0x03, 0x20, 0xcc, 0x11, 0x38, 0x78, 0x44,
0xc4, 0x60, 0x01, 0xcc, 0x20, 0x00, 0x0f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
0xff, 0xfe, 0xde, 0xce, 0xce, 0x1e, 0x1e, 0xde, 0xde, 0xde, 0x1e, 0x38, 0x31, 0xb2, 0x92, 0x92,
0x92, 0xb2, 0x39, 0x7c, 0x3e, 0x9e, 0xde, 0xde, 0x5e, 0x1e, 0x8e, 0xce, 0xce, 0xfe, 0xff, 0xfe,
0xf7, 0xef, 0xff, 0xff, 0xff, 0xef, 0xe6, 0xf6, 0xfb, 0xd9, 0x4c, 0x60, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xf4, 0x6c, 0xd9, 0xfb, 0xf3, 0xf6, 0xef, 0xef, 0xff, 0xff, 0xff, 0xe7, 0xf3,
0xf8, 0xf1, 0x01, 0x03, 0x07, 0xe3, 0xf1, 0x71, 0x31, 0x11, 0x18, 0x00, 0x00, 0x01, 0x01, 0x03,
0x03, 0x01, 0x00, 0x00, 0x18, 0x11, 0x31, 0x71, 0xf1, 0xf1, 0xc3, 0x03, 0x01, 0x01, 0xf8, 0xf8,
0x1f, 0x3f, 0x20, 0x00, 0x00, 0x3f, 0x03, 0x00, 0x80, 0x00, 0x00, 0x80, 0xc3, 0xc1, 0xc1, 0x01,
0x83, 0xc1, 0xc1, 0x83, 0x00, 0x00, 0x80, 0x80, 0x01, 0x1f, 0x3f, 0x00, 0x00, 0x3f, 0x3f, 0x1f,
0x1e, 0x00, 0x38, 0x38, 0x9c, 0xc6, 0x60, 0xff, 0xff, 0xf8, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xfe, 0x62, 0xce, 0x9c, 0x38, 0x18, 0x00, 0x1f,
0xfe, 0xf8, 0x07, 0x17, 0x13, 0x08, 0x1c, 0x3f, 0x3f, 0x7f, 0xf3, 0x80, 0x1f, 0x7f, 0xff, 0xff,
0xff, 0xff, 0x7f, 0x07, 0xc1, 0x7f, 0x3f, 0x3f, 0x3f, 0x0c, 0x09, 0x17, 0x17, 0x03, 0xfe, 0xfe
    };

    oled_write_raw_P(gimli_face, sizeof(gimli_face));
}

static void print_status_narrow(void) {
    // Print current mode
    // oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    // oled_write_ln_P(PSTR("layer"), false);
    render_face();
    oled_set_cursor(0,12);
    switch (get_highest_layer(layer_state)) {
        case _HANDS_DOWN:
            oled_write_P(PSTR("Hands Down Neu\n"), false);
            break;
        case _QWERTY:
            oled_write_P(PSTR("QWERTY\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case _BYOBU_NAV:
            oled_write_P(PSTR("Lower"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adj\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n"), false);
    // led_t led_usb_state = host_keyboard_led_state();
    // oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
}

#endif


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;

        case KC_BYOBU_NAV:
            if (record->event.pressed) {
                layer_on(_BYOBU_NAV);
                update_tri_layer(_BYOBU_NAV, _RAISE, _ADJUST);
            } else {
                layer_off(_BYOBU_NAV);
                update_tri_layer(_BYOBU_NAV, _RAISE, _ADJUST);
            }
            return false;

        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_BYOBU_NAV, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_BYOBU_NAV, _RAISE, _ADJUST);
            }
            return false;

        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;

        case KC_NUMROW:
            if (record->event.pressed) {
                layer_on(_NUMROW);
            } else {
                layer_off(_NUMROW);
            }
            return false;

        // case KC_PRVWD:
        //     if (record->event.pressed) {
        //         register_code(KC_LALT);
        //         register_code(KC_LEFT);
        //     } else {
        //         unregister_code(KC_LALT);
        //         unregister_code(KC_LEFT);
        //     }
        //     break;

        case KC_UNDO:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_Z);
            } else {
                unregister_code(KC_LGUI);
                unregister_code(KC_Z);
            }
            break;

        // case KC_REDO:
        //     if (record->event.pressed) {
        //         register_code(KC_LGUI);
        //         register_code(KC_LSFT);
        //         register_code(KC_Z);
        //     } else {
        //         unregister_code(KC_LGUI);
        //         unregister_code(KC_LSFT);
        //         unregister_code(KC_Z);
        //     }
        //     break;

        // case KC_CLAW:
        //     if (record->event.pressed) {
        //         register_code(KC_LGUI);
        //         register_code(KC_LALT);
        //         register_code(KC_LSFT);
        //         register_code(KC_S);
        //     } else {
        //         unregister_code(KC_LGUI);
        //         unregister_code(KC_LALT);
        //         unregister_code(KC_LSFT);
        //         unregister_code(KC_S);
        //     }
        //     break;

        // case KC_MDAQ:
        //     if (record->event.pressed) {
        //         SEND_STRING("@media #{$break}");
        //         tap_code16(KC_LEFT);
        //         tap_code16(KC_LEFT);
        //     }
        //     break;
    }
    return true;
}

// Two Encoder Support
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch(biton32(layer_state)) {
        case _QWERTY:
            alt_tab_timer = timer_read();
            if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                register_code(KC_LALT);
            }
            if (clockwise) {
                tap_code16(KC_TAB);
            } else {
                tap_code16(S(KC_TAB));
            }
            break;

        case _BYOBU_NAV:
            if (clockwise) {
                tap_code(KC_RGHT);
            } else {
                tap_code(KC_LEFT);
            }
            break;

        case _ADJUST:
            if (clockwise) {
                rgblight_step();
            } else {
                rgblight_step_reverse();
            }
            break;
        }

    } else if (index == 1) {
        switch(biton32(layer_state)) {
        case _QWERTY:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
        case _RAISE:
            if (clockwise) {
                register_code16(KC_LGUI);
                register_code16(KC_LALT);
                tap_code(KC_RGHT);
                unregister_code16(KC_LGUI);
                unregister_code16(KC_LALT);
            } else {
                register_code16(KC_LGUI);
                register_code16(KC_LALT);
                tap_code(KC_LEFT);
                unregister_code16(KC_LGUI);
                unregister_code16(KC_LALT);
            }
            break;

        case _ADJUST:
            if (clockwise) {
                rgblight_increase_hue();
            } else {
                rgblight_decrease_hue();
            }
            break;
        }
    }
    return true;
}


// Lighting layers
// const rgblight_segment_t PROGMEM chewies_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {7, 4, HSV_RED}, // Light 2 LEDs, starting with 35 and ending on 36
//     {44, 4, HSV_RED}  // Light 2 LEDs
// );
// const rgblight_segment_t PROGMEM chewies_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS( // default layer
//     {7, 4, HSV_PURPLE}, // Light 2 LEDs
//     {44, 4, HSV_PURPLE}  // Light 2 LEDs
// );
// const rgblight_segment_t PROGMEM chewies_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS( // Raise layer
//     {7, 4, HSV_BLUE}, // Light 2 LEDs
//     {44, 4, HSV_BLUE}//,  // Light 2 LEDs
//     //{45, 1, HSV_TEAL},  // Light 1 LED under I
//     //{51, 3, HSV_TEAL}  // Light 3 LEDs under J,K,L
// );


// // The array of lighting layers. Latter layers take precedence.
// const rgblight_segment_t* const PROGMEM chewies_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
//     chewies_capslock_layer,
//     chewies_layer1_layer, // Overrides caps lock layer
//     chewies_layer2_layer

// );

// // enable the lighting layers
// void keyboard_post_init_user(void) {
//     rgblight_layers = chewies_rgb_layers;
// }

// // turn on caps lock lighting layer
// bool led_update_user(led_t led_state) {
//     rgblight_set_layer_state(0, led_state.caps_lock);
//     return true;
// }

// // default state
// // layer_state_t default_layer_state_set_user(layer_state_t state) {
// //     rgblight_set_layer_state(1, layer_state_cmp(state, _QWERTY));
// //     return state;
// // }

// // Raise and Lower states
// layer_state_t layer_state_set_user(layer_state_t state) {
//     rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
//     rgblight_set_layer_state(3, layer_state_cmp(state, _BYOBU_NAV));
//     return state;
// }

// Runs just one time when the keyboard initializes.
void matrix_scan_user(void) {
    static bool has_ran_yet = false;
    if (!has_ran_yet) {
        has_ran_yet = true;
        // rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 3);
        // rgblight_mode(RGBLIGHT_MODE_BREATHING + 1);
        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_sethsv(HSV_WHITE);
    }
    if (is_alt_tab_active) {
      if (timer_elapsed(alt_tab_timer) > 750) {
        unregister_code(KC_LALT);
        is_alt_tab_active = false;
      }
    }
};


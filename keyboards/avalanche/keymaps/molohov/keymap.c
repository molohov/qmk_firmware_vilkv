
/*
qmk compile -kb avalanche/rev2 -km default_rev2
qmk flash -kb avalanche/rev2 -km default_rev2
*/

#include QMK_KEYBOARD_H

enum layer {
    _HANDS_DOWN,
    _BYOBU_NAV,
    _QWERTY_GAME,
    _NUMROW,
};

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum custom_keycodes {
    KC_HANDS_DOWN = SAFE_RANGE,
    KC_QWERTY_GAME,
    VIMWRITE,
    VIMWRITEQUIT,
    VIMQUIT,
    VIMQUITALL,
    VIPASTE,
    LNX_LAST,
    KU_QU,
};

#define  ESCNUM         LT(_NUMROW, KC_ESC)
#define  SPCNAV         LT(_BYOBU_NAV, KC_SPC)
#define  SFTBSP         SFT_T(KC_BSPC)
#define  CTLTAB         CTL_T(KC_TAB)
#define  ALTENT         ALT_T(KC_ENT)
#define  GUIDEL         GUI_T(KC_DEL)
#define  QWERTY_GAME    TG(_QWERTY_GAME)
#define  NUMTOG         TG(_NUMROW)
#define  PC_UNDO        C(KC_Z)
#define  PC_CUT         C(KC_X)
#define  PC_COPY        C(KC_C)
#define  PC_PASTE       C(KC_V)
#define  PC_FIND        C(KC_F)
#define  PC_LOCK        G(KC_L)
#define  PC_BSWD        C(KC_BSPC)
#define  PC_SLACK       A(KC_Q)
#define  PC_SCRNSHT     G(S(KC_S))
#define  PC_LWRD        C(KC_LEFT)
#define  PC_RWRD        C(KC_RIGHT)
#define  PC_CLIP        G(KC_V)
#define  LNX_PASTE      S(C(KC_V))
#define  LNX_LWD        A(KC_B)
#define  LNX_RWD        A(KC_F)
// reverse search
#define  LNX_RSR        C(KC_R)
#define  BY_VSPL        C(KC_F2)
#define  BY_HSPL        S(KC_F2)
// change layout
#define  BY_CLYT        S(KC_F8)
// fullscreen pane
#define  BY_FPNE        S(KC_F11)
// kill pane
#define  BY_KPNE        C(KC_F6)
// disable function keys
#define  BY_DISF        S(KC_F12)
#define  BY_MVWL        S(C(KC_F3))
#define  BY_MVWR        S(C(KC_F4))
#define  VS_CTLP        C(KC_P)
#define  VS_SCTP        S(C(KC_P))
#define  VS_COMT        C(KC_SLSH)
#define  VS_TERM        C(KC_GRV)
#define  VS_CODE        C(KC_1)

#ifdef HRM
#define HRM_N CTL_T(KC_N)
#define HRM_T ALT_T(KC_T)
#define HRM_A SFT_T(KC_A)
#define HRM_E CTL_T(KC_E)
#define HRM_I ALT_T(KC_I)
#define HRM_H GUI_T(KC_H)
#else
#define HRM_N KC_N
#define HRM_T KC_T
#define HRM_A KC_A
#define HRM_E KC_E
#define HRM_I KC_I
#define HRM_H KC_H
#endif

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
                KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                               KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,
                KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                               KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSPC,
    XXXXXXX,    KC_LSFT,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_LCBR,    KC_RCBR,    KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,    KC_BSLS,
                KC_LCTL,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_BSPC,    KC_EQL,     KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    XXXXXXX,
                                        XXXXXXX,    KC_LCTL,    KC_SPC,     KC_LSFT,    KC_ENT,     _______,    _______,    _______,    _______,    KC_MUTE
 * ),
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_HANDS_DOWN] = LAYOUT(
                VS_CODE,    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                               KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       VS_TERM,
                VS_CTLP,    KC_X,       KC_F,       KC_M,       KC_P,       KC_B,                               KC_MINS,    KC_SLSH,    KC_DOT,     KC_COMM,    KC_Q,       LNX_RSR,
    VIPASTE,    KC_Z,       KC_R,       KC_S,       HRM_N,      HRM_T,      KC_G,       PC_LOCK,    KC_MPLY,    KC_QUOT,    HRM_A,      HRM_E,      HRM_I,      HRM_H,      KC_J,       PC_SCRNSHT,
                KC_HOME,    KC_W,       KC_C,       KC_L,       KC_D,       KC_V,       PC_BSWD,    PC_SLACK,   KC_EQL,     KC_U,       KC_O,       KC_Y,       KC_K,       KC_END,
                                        NUMTOG,     VS_COMT,    GUIDEL,     SFTBSP,     CTLTAB,     ALTENT,     SPCNAV,     ESCNUM,     PC_CLIP,    QWERTY_GAME
    ),

    [_BYOBU_NAV] = LAYOUT(
                KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,                              KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,
                VS_SCTP,    KC_AMPR,    KC_GRV,     KC_HASH,    KC_LBRC,    KC_RBRC,                            XXXXXXX,    PC_LWRD,    KC_UP,      PC_RWRD,    XXXXXXX,    XXXXXXX,
    XXXXXXX,    KC_BSLS,    KC_COLN,    KC_PERC,    KC_PAST,    KC_LPRN,    KC_RPRN,    XXXXXXX,    XXXXXXX,    LNX_LWD,    KC_LEFT,    KC_DOWN,    KC_RGHT,    LNX_RWD,    XXXXXXX,    XXXXXXX,
                BY_KPNE,    BY_DISF,    BY_VSPL,    BY_HSPL,    BY_CLYT,    BY_FPNE,    _______,    _______,    KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F8,      KC_F6,
                                        BY_MVWL,    BY_MVWR,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______
    ),

    [_NUMROW] = LAYOUT(
                _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                            XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,
                XXXXXXX,    KC_BSLS,    KC_ASTR,    KC_X,       KC_GRV,     _______,                            _______,    _______,    _______,    _______,    _______,    _______,
    XXXXXXX,    KC_LBRC,    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       _______,    _______,    KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_RBRC,    _______,
                _______,    KC_COLN,    KC_PERC,    KC_LPRN,    KC_RPRN,    _______,    _______,    _______,    KC_EQL,     KC_PPLS,    KC_PMNS,    KC_PAST,    KC_PSLS,    _______,
                                        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______
    ),

    [_QWERTY_GAME] = LAYOUT(
                KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                               KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,
                KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                               KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSPC,
    XXXXXXX,    KC_LSFT,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_LCBR,    KC_RCBR,    KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,    KC_BSLS,
                KC_LCTL,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_BSPC,    KC_EQL,     KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    XXXXXXX,
                                        XXXXXXX,    KC_LCTL,    KC_SPC,     KC_LSFT,    KC_ENT,     _______,    _______,    _______,    _______,    KC_MUTE
    ),
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
        case _QWERTY_GAME:
            oled_write_P(PSTR("QWERTY_GAME\n"), false);
            break;
        case _BYOBU_NAV:
            oled_write_P(PSTR("ByobuNav"), false);
            break;
        case _NUMROW:
            oled_write_P(PSTR("NumSym"), false);
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

// #ifdef COMBO_ENABLE
// COMBOS
enum combo_events {
    COMBO_VIM_WRITE,
    COMBO_VIM_WRITEQUIT,
    COMBO_VIM_QUIT,
    COMBO_VIM_QUITALL,
    COMBO_VIM_SHIFTV,
    COMBO_PC_COPY,
    COMBO_PC_CUT,
    COMBO_PC_PASTE,
    COMBO_PC_FIND,
    COMBO_PC_UNDO,
    COMBO_LNX_RSRCH,
    COMBO_LNX_LAST,
    COMBO_KU_QU,
    COMBO_EXCLAMATION,
    COMBO_DEL_WORD,
    COMBO_SEMICOLON,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

// vim combos rooted from left home row middle finger
// const uint16_t PROGMEM vimwrite[] =     {KC_N, KC_T, COMBO_END};
// const uint16_t PROGMEM vimwritequit[] = {KC_N, KC_D, COMBO_END};
// const uint16_t PROGMEM vimquit[] =      {KC_N, KC_G, COMBO_END};
// const uint16_t PROGMEM vimquitall[] =   {KC_N, KC_B, COMBO_END};
// const uint16_t PROGMEM vimshiftv[] =    {KC_N, KC_P, COMBO_END};

// copy/paste combos on left bottom row
const uint16_t PROGMEM pc_undo[] =      {KC_W, KC_C, COMBO_END};
const uint16_t PROGMEM pc_copy[] =      {KC_C, KC_L, COMBO_END};
const uint16_t PROGMEM pc_cut[] =       {KC_C, KC_N, COMBO_END};
const uint16_t PROGMEM pc_paste[] =     {KC_L, KC_D, COMBO_END};
const uint16_t PROGMEM pc_find[] =      {KC_L, KC_T, COMBO_END};

// vim combos rooted from right home row middle finger
const uint16_t PROGMEM vimwrite[] =     {KC_E, KC_A,    COMBO_END};
const uint16_t PROGMEM vimwritequit[] = {KC_E, KC_U,    COMBO_END};
const uint16_t PROGMEM vimquit[] =      {KC_E, KC_QUOT, COMBO_END};
const uint16_t PROGMEM vimquitall[] =   {KC_E, KC_MINS, COMBO_END};
// keep shift+V on the left side
const uint16_t PROGMEM vimshiftv[] =    {KC_N, KC_D, COMBO_END};
// const uint16_t PROGMEM vimshiftv[] =    {KC_E, KC_SLSH, COMBO_END};

// linux combos rooted from right home row ring finger
const uint16_t PROGMEM lnx_rsearch[] =  {KC_I, KC_E,    COMBO_END};
const uint16_t PROGMEM lnx_last[] =     {KC_I, KC_DOT,  COMBO_END};

const uint16_t PROGMEM ku_qu[] =        {KC_U, KC_K,    COMBO_END};
// const uint16_t PROGMEM shft_ku_qu[] =   {KC_LSFT, KC_U, KC_K,    COMBO_END};

const uint16_t PROGMEM exclamation[] =  {KC_A, KC_DOT,    COMBO_END};
// . + , = ;
const uint16_t PROGMEM semicolon[] =    {KC_DOT, KC_COMM,    COMBO_END};

// this combo mirrors the DW action in vim!
const uint16_t PROGMEM del_word[] =     {KC_W, KC_D,    COMBO_END};

combo_t key_combos[] = {
    [COMBO_VIM_WRITE]     = COMBO(vimwrite,       VIMWRITE),
    [COMBO_VIM_WRITEQUIT] = COMBO(vimwritequit,   VIMWRITEQUIT),
    [COMBO_VIM_QUIT]      = COMBO(vimquit,        VIMQUIT),
    [COMBO_VIM_QUITALL]   = COMBO(vimquitall,     VIMQUITALL),
    [COMBO_VIM_SHIFTV]    = COMBO(vimshiftv,      S(KC_V)),
    [COMBO_PC_COPY]       = COMBO(pc_copy,        PC_COPY),
    [COMBO_PC_CUT]        = COMBO(pc_cut,         PC_CUT),
    [COMBO_PC_PASTE]      = COMBO(pc_paste,       PC_PASTE),
    [COMBO_PC_FIND]       = COMBO(pc_find,        PC_FIND),
    [COMBO_PC_UNDO]       = COMBO(pc_undo,        PC_UNDO),
    [COMBO_LNX_RSRCH]     = COMBO(lnx_rsearch,    C(KC_R)),
    [COMBO_LNX_LAST]      = COMBO(lnx_last,       LNX_LAST),
    [COMBO_KU_QU]         = COMBO(ku_qu,          KU_QU),
    [COMBO_EXCLAMATION]   = COMBO(exclamation,    KC_EXLM),
    [COMBO_SEMICOLON]     = COMBO(semicolon,      KC_SCLN),
    [COMBO_DEL_WORD]      = COMBO(del_word,       C(KC_DEL)),
};

// #endif

// CUSTOM KEYSTROKES
bool process_adaptive_key(uint16_t keycode, const keyrecord_t *record) {
    bool return_state = true; // assume we don't do anything.
    static uint16_t prior_keycode = KC_NO; // for process_adaptive_key
    static uint16_t prior_keydown = 0;

    if (record->event.pressed) {
        keycode = keycode & 0xFF; // ignore all mods? or just shift?
        if ((timer_elapsed(prior_keydown) < ADAPTIVE_TERM)) {
            switch (keycode) {
                case KC_M:
                    switch (prior_keycode) {
                        case KC_F: // FM -> FL
                        case KC_P: // PM -> PL
                        case KC_B: // BM -> BL
                            tap_code(KC_L);
                            return_state = false; // done.
                    }
                    break;
                // case KC_W:
                //     switch (prior_keycode) {
                //         case KC_C: //CW -> CR
                //             tap_code(KC_R);
                //             return_state = false; // done.
                //     }
                //     break;
                case KC_F:
                    switch (prior_keycode) {
                        case KC_X: //XF -> XC
                            tap_code(KC_C);
                            return_state = false; // done.
                    }
                    break;
/*
// Left hand adaptives (most are single-handed, bc speed, dexterity limits)
*/

                // case KC_D:
                // case KC_F:
                //     switch (prior_keycode) {
                //         case KC_B:
                //         case KC_K:
                //             unregister_code(KC_LSFT); // remove shift here.
                //             unregister_code(KC_RSFT); // remove shift here.
                //             tap_code(KC_L);
                //             return_state = false; // done.
                //             break;
                //         case KC_M: // LF
                //             tap_code(KC_BSPC);
                //             tap_code(KC_L);
                //             tap_code16(keycode);
                //             return_state = false; // done.
                //             break;
                //         case KC_P:
                //             tap_code(KC_S);
                //             return_state = false; // done.
                //     }
                //     break;
                // case KC_G:
                //     switch (prior_keycode) {
                //         case KC_I: // IG =
                //             send_string("ng ");
                //             return_state = false; // done.
                //     }
                //     break;
                // case KC_L:
                //     switch (prior_keycode) {
                //         case KC_M: // ML = LL
                //             tap_code(KC_BSPC);
                //             tap_code(KC_L);
                //             tap_code16(keycode);
                //             return_state = false; // done.
                //     }
                //     break;

//                 case KC_N: // Do we need to watch for more?
//                     switch (prior_keycode) {
//                         case KC_P: // is this needed?
//                             unregister_code(KC_LSFT); // remove shift here.
//                             unregister_code(KC_RSFT); // remove shift here.
//                             tap_code(KC_H); // quickly typing "?n" yields "?h"
//                             return_state = false; // done.
//                             break;
//                         case KC_T: // demonstrator. TN combo is "TH" digraph
//                             send_string("ion");
//                             return_state = false; // done.
//                             break;
//                     }
//                     break;
//                 case KC_P:
//                     switch (prior_keycode) {
//                         case KC_J: // "jp" is "Japan"…ese? A demonstrator AK
//                             tap_code(KC_BSPC);
//                             register_code(KC_LSFT); // shift here.
//                             tap_code(KC_J); // this should always be cap
//                             unregister_code(KC_LSFT); // remove shift here.
//                             unregister_code(KC_RSFT); // remove shift here.
//                             send_string("apan");
//                             return_state = false; // done.
//                             break;
//                         case KC_H: // "hp" is "lp" on Platinum
//                             tap_code(KC_BSPC);
//                             unregister_code(KC_LSFT); // remove shift here.
//                             unregister_code(KC_RSFT); // remove shift here.
//                             tap_code(KC_L);
//                             tap_code16(keycode);
//                             return_state = false; // done.
//                             break;
//                         case KC_B:
//                         case KC_K:
//                         case KC_V: // quickly typing "?p" yields "?l"
//                             unregister_code(KC_LSFT); // remove shift here.
//                             unregister_code(KC_RSFT); // remove shift here.
//                             tap_code(KC_L);
//                             return_state = false; // done.
//                             break;
//                         case KC_M:
//                         case KC_F: // "f?" is really uncommon, we prolly want "l?"
//                             tap_code(KC_BSPC);
//                             unregister_code(KC_LSFT); // remove shift here.
//                             unregister_code(KC_RSFT); // remove shift here.
//                             tap_code(KC_L);
//                             tap_code16(keycode);
//                             return_state = false; // done.
//                     }
//                     break;
//                 case KC_T:
//                     switch (prior_keycode) {
//                         case KC_K: // ML = LL
//                             tap_code(KC_L);
//                             return_state = false; // done.
//                     }
//                     break;
//                 case KC_U:
//                     switch (prior_keycode) {
//                         case KC_Y: // YU = You bc YO is a tad awk, but yu is easy, and uncommon
//                             unregister_code(KC_LSFT); // remove shift here.
//                             unregister_code(KC_RSFT); // remove shift here.
//                             tap_code(KC_O);
//                             tap_code(KC_U);
//                             return_state = false; // done.
//                     }
//                     break;
//                 case KC_B: // take advantage of B & V being phonotacically similar
//                 case KC_V: // (and in same finger/column) to process as adaptive key
//                     switch (prior_keycode) {
//                         case KC_M:
//                         case KC_N:
//                             tap_code(KC_B); // "v" is likely a "b"
//                             return_state = false; // done.
//                             break;
//                         case KC_F:
//                         case KC_P:  /* this is for bronze */
//                             tap_code(KC_BSPC); // get rid of the prior
//                             tap_code(KC_L); // quickly typing "p?" yields "l?"
//                             tap_code16(keycode); //
//                             return_state = false; // done.
//                             break;
//                         case KC_H: /* mostly for platinum */
//                            tap_code(KC_L); // quickly typing "hv" yields "lh"
//                     }
//                     break;

//                 case KC_S:
//                     switch (prior_keycode) { // demonstrator. SN combo is "SH" digraph
//                         case KC_T:
//                             tap_code(KC_N);
//                         case KC_N:
//                             send_string("ess");
//                             return_state = false; // done.
//                             break;
//                     }
//                     break;

//                 case KC_J: // SAME-HAND TOWARD PINKY ISSUES
//                 case KC_W: // adjacent fingers don't do next row as easily,
//                 case KC_X: // especially on ring to pinky.
//                     switch (prior_keycode) {
//                         case KC_B: //
//                         case KC_C: // RING TO PINKY This softens the burden,
//                         case KC_D: //
//                         case KC_F: // and equalizes column-stagger & ortho boards.
//                         case KC_G: //
//                         case KC_M: // anything that is statistically much more frequent
//                         case KC_P: // bc why not?
//                         case KC_V: //
//                             unregister_code(KC_LSFT); // remove shift here.
//                             unregister_code(KC_RSFT); // remove shift here.
//                             tap_code16(KC_R);
//                             return_state = false; // done.
//                             break;
//                         case KC_L: // repeater (For Platinum's thumb-L)
//                             tap_code16(KC_L); // LW isn't likely, so we'll leave it for the sake of smaller code
//                             return_state = false; // done.
//                             break;
//                     }
//                     break;

// /*
// // right hand adaptives
// */

//                case KC_A:
//                     switch (prior_keycode) {
//                         case KC_COMM:
//                             tap_code(KC_BSPC); // get rid of the prior
//                             tap_code(KC_U); // quickly typing ",A" yields "UA"
//                             tap_code16(keycode); //
//                             return_state = false; // done.
//                             break;
//                     }
//                     break;
//                 case KC_MINS:
//                      switch (prior_keycode) {
//                          case KC_L:
//                              tap_code16(prior_keycode); // repeater (For Platinum's thumb-L)
//                              return_state = false; // done.
//                              break;
//                      }
//                      break;
//                 case KC_COMM:
//                     switch (prior_keycode) {
//                         case KC_A:
//                             tap_code(KC_U); // quickly typing "A," yields "AU"
//                             return_state = false; // done.
//                             break;
//                     }
//                     break;
            }
        }
        prior_keycode = keycode;
        prior_keydown = timer_read(); // (re)start prior_key timing
    }
    return return_state; //
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Do we handle an adaptive key?
    if (!process_adaptive_key(keycode, record)) {
        return false; // took care of that key
    }
    switch (keycode) {
        // case KC_QWERTY_GAME:
        //     if (record->event.pressed) {
        //         set_single_persistent_default_layer(_QWERTY_GAME);
        //     }
        //     return false;

        case VIMWRITE:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_ESCAPE) SS_DELAY(100) SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_TAP(X_W) SS_DELAY(100) SS_TAP(X_ENTER));
            }
            break;

        case VIMWRITEQUIT:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_ESCAPE) SS_DELAY(100) SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_TAP(X_X) SS_DELAY(100) SS_TAP(X_ENTER));
            }
            break;

        case VIMQUIT:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_ESCAPE) SS_DELAY(100) SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_TAP(X_Q) SS_DELAY(100) SS_LSFT(SS_TAP(X_1)) SS_DELAY(100) SS_TAP(X_ENTER));
            }
            break;

        case VIMQUITALL:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_ESCAPE) SS_DELAY(100) SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_TAP(X_Q) SS_DELAY(100) SS_TAP(X_A) SS_DELAY(100) SS_TAP(X_ENTER));
            }
            break;

        case VIPASTE:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_V) SS_DELAY(100) SS_TAP(X_SPACE) SS_DELAY(100) SS_LCTL(SS_LSFT(SS_TAP(X_V))) SS_DELAY(100) SS_TAP(X_ENTER));
            }
        case LNX_LAST:
            if (record->event.pressed) {
              SEND_STRING(SS_LSFT(SS_TAP(X_1)) SS_DELAY(100) SS_LSFT(SS_TAP(X_4)) SS_DELAY(100) SS_TAP(X_SPACE));
            }
            break;
        case KU_QU:
            if (record->event.pressed) {
                SEND_STRING("qu");
            }
            break;
    }
    return true;
}


// Two Encoder Support
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch(biton32(layer_state)) {
        case _HANDS_DOWN:
            if (clockwise) {
                tap_code(KC_PGDN);
            } else {
                tap_code(KC_PGUP);
            }
            break;
        case _BYOBU_NAV:
            if (clockwise) {
                tap_code16(C(G(KC_RIGHT)));
            } else {
                tap_code16(C(G(KC_LEFT)));
            }
            break;
        }

    } else if (index == 1) {
        switch(biton32(layer_state)) {
        case _HANDS_DOWN:
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
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
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
// //     rgblight_set_layer_state(1, layer_state_cmp(state, _QWERTY_GAME));
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
      if (timer_elapsed(alt_tab_timer) > 600) {
        unregister_code(KC_LALT);
        is_alt_tab_active = false;
      }
    }
};


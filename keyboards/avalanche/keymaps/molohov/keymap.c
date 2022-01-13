
/*
qmk compile -kb avalanche/rev2 -km default_rev2
qmk flash -kb avalanche/rev2 -km default_rev2
*/

#include QMK_KEYBOARD_H

enum layer {
    _HANDS_DOWN,
    _NAV_NUM_SYM,
    _QWERTY_GAME,
    _BYO_ONOTE_VSC,
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
    DLSIM,
    SLACK_CODE,
    SLACK_CODE_PASTE,
    COPY_PASTE,
    IMPORT_PDB,
};

#define  ESCBYO         LT(_BYO_ONOTE_VSC, KC_ESC)
#define  SPCNAV         LT(_NAV_NUM_SYM, KC_SPC)
#define  SFTBSP         SFT_T(KC_BSPC)
#define  CTLTAB         CTL_T(KC_TAB)
#define  ALTENT         ALT_T(KC_ENT)
#define  GUIDEL         GUI_T(KC_DEL)
#define  QWERTY_GAME    TG(_QWERTY_GAME)
#define  NUMTOG         TG(_NAV_NUM_SYM)
#define  PC_UNDO        C(KC_Z)
#define  PC_SALL        C(KC_A)
#define  PC_CUT         C(KC_X)
#define  PC_COPY        C(KC_C)
#define  PC_PASTE       C(KC_V)
#define  PC_FIND        C(KC_F)
#define  PC_LOCK        G(KC_L)
#define  PC_BSWD        C(KC_BSPC)
#define  PC_SLACK       A(KC_Q)
#define  PC_SCSH        G(S(KC_S))
#define  PC_LWRD        C(KC_LEFT)
#define  PC_RWRD        C(KC_RIGHT)
#define  ALTESC         ALT_T(KC_ESC)
#define  WINRUN         C(A(KC_K))
#define  LNX_PASTE      S(C(KC_V))
#define  LNX_LWD        A(KC_B)
#define  LNX_RWD        A(KC_F)
// reverse search
#define  LNX_RSR        C(KC_R)
// vertical split
#define  BY_VSPL        C(KC_F2)
// horizontal split
#define  BY_HSPL        S(KC_F2)
// change layout
#define  BY_CLYT        S(KC_F8)
// fullscreen pane
#define  BY_FPNE        S(KC_F11)
// kill pane
#define  BY_KPNE        C(KC_F6)
// disable function keys
#define  BY_DISF        S(KC_F12)
// move window left
#define  BY_MVWL        S(C(KC_F3))
// move window right
#define  BY_MVWR        S(C(KC_F4))
// shift pane focus left
#define  BY_FSPL        S(KC_F3)
// shift pane focus right
#define  BY_FSPR        S(KC_F4)
// new pane
#define  BY_NWIN        KC_F2
// focus on left window
#define  BY_FSWL        KC_F3
// focus on right window
#define  BY_FSWR        KC_F4
// refresh settings
#define  BY_RFSH        KC_F5
// exit server
#define  BY_KSRV        KC_F6
// rename window
#define  BY_RNWN        KC_F8
#define  VS_CTLP        C(KC_P)
#define  VS_SCTP        S(C(KC_P))
#define  VS_COMT        C(KC_SLSH)
// focus on terminal
#define  VS_TERM        C(KC_GRV)
// focus on code area
#define  VS_EDIT        C(KC_1)
// go to next editor
#define  VS_NEDT        C(KC_PGDN)
// go to prev editor
#define  VS_PEDT        C(KC_PGUP)

// to-do
#define ON_TODO         C(KC_1)
// important
#define ON_IMPT         C(KC_2)
// question
#define ON_QUES         C(KC_3)

#define PY_IPDB         IMPORT_PDB

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
#define MODS_SHIFT (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define SEND_CAP_STRING(str, capitalized) if (MODS_SHIFT) { \
                                            clear_mods(); \
                                            SEND_STRING(capitalized); \
                                          } else { \
                                            SEND_STRING(str); \
                                          }

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
                VS_EDIT,    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                               KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       VS_TERM,
                VS_CTLP,    KC_X,       KC_F,       KC_M,       KC_P,       KC_B,                               KC_MINS,    KC_DOT,     KC_SLSH,    KC_COMM,    KC_Q,       LNX_RSR,
    PC_SCSH,    KC_Z,       KC_R,       KC_S,       HRM_N,      HRM_T,      KC_G,       PC_LOCK,    KC_MPLY,    KC_QUOT,    HRM_A,      HRM_E,      HRM_I,      HRM_H,      KC_J,       VIPASTE,
                KC_HOME,    KC_W,       KC_C,       KC_L,       KC_D,       KC_V,       PC_BSWD,    PC_SLACK,   KC_EQL,     KC_U,       KC_O,       KC_Y,       KC_K,       KC_END,
                                        WINRUN,     ALTESC,     GUIDEL,     SFTBSP,     CTLTAB,     ALTENT,     SPCNAV,     ESCBYO,     VS_COMT,    QWERTY_GAME
    ),

    [_NAV_NUM_SYM] = LAYOUT(
                _______,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,                              KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     _______,
                _______,    KC_AMPR,    KC_PERC,    KC_BSLS,    KC_LBRC,    KC_RBRC,                            _______,    _______,    KC_UP,      _______,    _______,    _______,
    _______,    KC_SLSH,    KC_COLN,    KC_GRV,     KC_PAST,    KC_LPRN,    KC_RPRN,    _______,    _______,    _______,    KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_EQL,     _______,    _______,
                _______,    KC_7,       KC_3,       KC_1,       KC_5,       KC_9,       KC_F11,     KC_F12,     KC_8,       KC_2,       KC_0,       KC_4,       KC_6,       _______,
                                        _______,    KC_LALT,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______
    ),

    [_BYO_ONOTE_VSC] = LAYOUT(
                CMB_OFF,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,                              KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     _______,
                CMB_ON,     _______,    _______,    _______,    _______,    _______,                            BY_FPNE,    BY_CLYT,    BY_HSPL,    BY_VSPL,    BY_DISF,    BY_KPNE,
    XXXXXXX,    _______,    ON_QUES,    ON_IMPT,    ON_TODO,    PY_IPDB,    _______,    _______,    _______,    BY_RNWN,    BY_FSPL,    BY_NWIN,    BY_FSPR,    BY_RFSH,    BY_KSRV,    XXXXXXX,
                _______,    VS_PEDT,    VS_NEDT,    VS_EDIT,    VS_TERM,    _______,    _______,    _______,    _______,    BY_FSWL,    BY_FSWR,    BY_MVWL,    BY_MVWR,    _______,
                                        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______
    ),

    [_QWERTY_GAME] = LAYOUT(
                KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                               KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,
                KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                               KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSPC,
    XXXXXXX,    KC_LSFT,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       _______,    _______,    KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,    KC_BSLS,
                KC_LCTL,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       _______,    _______,    KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    XXXXXXX,
                                        XXXXXXX,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______
    ),
};


#ifdef OLED_ENABLE

// static void render_logo(void) {

//     static const char PROGMEM gimli_logo[] = {
//         // 'gimli-logo', 128x32px
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf8, 0xf8, 0x7c, 0x7c, 0x3c, 0x3c, 0x3c, 0x3c,
//         0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x1c, 0x1c, 0x0c, 0x0c, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x0f, 0x8f, 0x8f, 0xcf, 0xc6,
//         0x02, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xff,
//         0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x0f, 0x8f, 0x8f, 0xcf, 0xc6, 0x02, 0x00,
//         0x18, 0x18, 0xb8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x78, 0xfc, 0xfe, 0xfe, 0xff,
//         0xff, 0xff, 0xff, 0xff, 0x7f, 0x7b, 0xf9, 0xf9, 0xf9, 0xf8, 0xf8, 0x78, 0xb8, 0x98, 0x18, 0x08,
//         0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
//         0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0xf8, 0xf8, 0xfc, 0x7e, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7e, 0xfc, 0xf8, 0xf8, 0xf0,
//         0xf0, 0xf8, 0xf8, 0xfc, 0x7e, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff,
//         0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00,
//         0x00, 0x00, 0xf0, 0xf0, 0xf8, 0xf8, 0x7c, 0x7e, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
//         0x00, 0x00, 0x01, 0x01, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x0f, 0x3f, 0x7f, 0x7f,
//         0xff, 0xff, 0xff, 0xf7, 0xe7, 0xe7, 0xc7, 0x87, 0x87, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x06, 0x07, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
//         0x00, 0x00, 0x00, 0x00, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01, 0x01,
//         0x01, 0x01, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff,
//         0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0xf8, 0xf8, 0x7c, 0x7e, 0x3e, 0x3f, 0x1f, 0x0f, 0x00,
//         0x00, 0x00, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x01, 0x03, 0x03, 0x07, 0x07, 0x0f, 0x0f, 0x1f, 0x3f, 0x3e, 0x3e, 0x3c, 0x3c, 0x3c,
//         0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x3f,
//         0x1f, 0x1f, 0x0f, 0x07, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x00, 0x00
//     };

//     oled_write_raw_P(gimli_logo, sizeof(gimli_logo));
// }

// static void render_face(void) {

//     static const char PROGMEM gimli_face[] = {
//         // 'gimli-face', 32x72px
// 0x3f, 0x3f, 0x1f, 0x1f, 0x8f, 0x8f, 0xcf, 0xc7, 0xc7, 0xc7, 0xc7, 0x01, 0x00, 0x00, 0xf8, 0xf8,
// 0xf8, 0x00, 0x01, 0x41, 0xe7, 0xc7, 0xc7, 0xc7, 0xc7, 0x8f, 0x8f, 0x1f, 0x1f, 0x3f, 0x7f, 0x7f,
// 0x1e, 0x1e, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0x00, 0x80, 0x30, 0x09, 0x01,
// 0x09, 0x30, 0x80, 0x00, 0x1f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3e, 0x1e, 0x1c,
// 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0x03, 0x20, 0xcc, 0x11, 0x38, 0x78, 0x44,
// 0xc4, 0x60, 0x01, 0xcc, 0x20, 0x00, 0x0f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
// 0xff, 0xfe, 0xde, 0xce, 0xce, 0x1e, 0x1e, 0xde, 0xde, 0xde, 0x1e, 0x38, 0x31, 0xb2, 0x92, 0x92,
// 0x92, 0xb2, 0x39, 0x7c, 0x3e, 0x9e, 0xde, 0xde, 0x5e, 0x1e, 0x8e, 0xce, 0xce, 0xfe, 0xff, 0xfe,
// 0xf7, 0xef, 0xff, 0xff, 0xff, 0xef, 0xe6, 0xf6, 0xfb, 0xd9, 0x4c, 0x60, 0xff, 0xff, 0xff, 0xff,
// 0xff, 0xff, 0xff, 0xf4, 0x6c, 0xd9, 0xfb, 0xf3, 0xf6, 0xef, 0xef, 0xff, 0xff, 0xff, 0xe7, 0xf3,
// 0xf8, 0xf1, 0x01, 0x03, 0x07, 0xe3, 0xf1, 0x71, 0x31, 0x11, 0x18, 0x00, 0x00, 0x01, 0x01, 0x03,
// 0x03, 0x01, 0x00, 0x00, 0x18, 0x11, 0x31, 0x71, 0xf1, 0xf1, 0xc3, 0x03, 0x01, 0x01, 0xf8, 0xf8,
// 0x1f, 0x3f, 0x20, 0x00, 0x00, 0x3f, 0x03, 0x00, 0x80, 0x00, 0x00, 0x80, 0xc3, 0xc1, 0xc1, 0x01,
// 0x83, 0xc1, 0xc1, 0x83, 0x00, 0x00, 0x80, 0x80, 0x01, 0x1f, 0x3f, 0x00, 0x00, 0x3f, 0x3f, 0x1f,
// 0x1e, 0x00, 0x38, 0x38, 0x9c, 0xc6, 0x60, 0xff, 0xff, 0xf8, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff,
// 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xfe, 0x62, 0xce, 0x9c, 0x38, 0x18, 0x00, 0x1f,
// 0xfe, 0xf8, 0x07, 0x17, 0x13, 0x08, 0x1c, 0x3f, 0x3f, 0x7f, 0xf3, 0x80, 0x1f, 0x7f, 0xff, 0xff,
// 0xff, 0xff, 0x7f, 0x07, 0xc1, 0x7f, 0x3f, 0x3f, 0x3f, 0x0c, 0x09, 0x17, 0x17, 0x03, 0xfe, 0xfe
//     };

//     oled_write_raw_P(gimli_face, sizeof(gimli_face));
// }

static void print_layers(void) {
    // Print current mode
    // oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    // oled_write_ln_P(PSTR("layer"), false);
    // render_face();
    // oled_set_cursor(0,12);
    // oled_write_P(PSTR("BUH'S"), false);
    // oled_write_P(PSTR("BOARD"), false);
    // oled_write_P(PSTR("\n"), false);
    switch (get_highest_layer(layer_state)) {
        case _HANDS_DOWN:
            // oled_write_P(PSTR("Hands"), false);
            // oled_write_ln_P(PSTR("Down"), false);
            // oled_write_ln_P(PSTR("Neu"), false);
            if (is_keyboard_master()) {
                oled_write_ln_P(PSTR("  VSCP X F M P B"), false);
                oled_write_P(   PSTR("SCRN Z R S N T G LOCK"), false);
                oled_write_P(   PSTR("  HOME W C L D V CBSP"), false);
                oled_write_P(   PSTR("NUM VC GDEL SBSP CTAB"), false);
            }
            break;
        case _QWERTY_GAME:
            // oled_write_P(PSTR("QWERT"), false);
            // oled_write_ln_P(PSTR("Game"), false);
            oled_write_ln_P(PSTR("ESC Q W E R T"), false);
            oled_write_ln_P(PSTR("SFT A S D F G"), false);
            oled_write_ln_P(PSTR("CTL Z X C V B"), false);
            oled_write_ln_P(PSTR("XXX CTL SPC SFT ENT"), false);
            break;
        case _NAV_NUM_SYM:
            // oled_write_P(PSTR("Navig"), false);
            // oled_write_P(PSTR("Symbs"), false);
            // oled_write_P(PSTR("Numbs"), false);
            oled_write_ln_P(PSTR("  F1 F2 F3 F4 F5"), false);
            oled_write_ln_P(PSTR("  &  \%  \\  [  ]"), false);
            oled_write_ln_P(PSTR("/ :  `  *  (  )"), false);
            oled_write_ln_P(PSTR("  7  3  1  5  9  F11"), false);
            break;
        case _BYO_ONOTE_VSC:
            // oled_write_P(PSTR("Byobu"), false);
            // oled_write_P(PSTR("ONote"), false);
            // oled_write_P(PSTR("VCode"), false);
            oled_write_P(PSTR("      OIM OTO OQS PDB"), false);
            oled_write_P(PSTR("KL DSF VSP HSP CL FPN"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
    // oled_write_P(PSTR("\n"), false);
    // led_t led_usb_state = host_keyboard_led_state();
    // oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
}

// static void print_mods(void) {
//     int current_mods = get_mods();
//     if (current_mods & MOD_MASK_SHIFT) {
//         oled_write_P(PSTR("SHIFT"), false);
//     }
//     if (current_mods & MOD_MASK_CTRL) {
//         oled_write_ln_P(PSTR("CTRL"), false);
//     }
//     if (current_mods & MOD_MASK_GUI) {
//         oled_write_ln_P(PSTR("GUI"), false);
//     }
//     if (current_mods & MOD_MASK_ALT) {
//         oled_write_ln_P(PSTR("ALT"), false);
//     }
// }

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
    return rotation;
}

void oled_task_user(void) {
    oled_clear();
    if (is_keyboard_master()) {
        print_layers();
        // print_mods();
    } else {
        print_layers();
        // render_logo();
        // print_mods();
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
    COMBO_PC_SELECTALL,
    COMBO_PC_COPYPASTE,
    COMBO_WIN_BLUETOOTH,
    COMBO_WIN_CLIP,
    COMBO_LNX_CLS,
    COMBO_LNX_LAST,
    COMBO_SLACK_CODE,
    COMBO_SLACK_CODE_PASTE,
    COMBO_KU_QU,
    // COMBO_EXCLAMATION,
    COMBO_AT,
    COMBO_DOLLAR,
    COMBO_DEL_WORD,
    COMBO_SEMICOLON,
    // COMBO_ESC,
    COMBO_DLSIM,
    COMBO_NEWTAB,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

// vim combos rooted from left home row middle finger
// const uint16_t PROGMEM vimwrite[] =     {KC_N, KC_T, COMBO_END};
// const uint16_t PROGMEM vimwritequit[] = {KC_N, KC_D, COMBO_END};
// const uint16_t PROGMEM vimquit[] =      {KC_N, KC_G, COMBO_END};
// const uint16_t PROGMEM vimquitall[] =   {KC_N, KC_B, COMBO_END};
// const uint16_t PROGMEM vimshiftv[] =    {KC_N, KC_P, COMBO_END};

// LEFT HAND
// copy/paste combos on left bottom row
const uint16_t PROGMEM pc_undo[]      = {KC_W, KC_C, COMBO_END};
const uint16_t PROGMEM pc_selectall[] = {KC_W, KC_L, COMBO_END};
const uint16_t PROGMEM pc_copy[]      = {KC_C, KC_L, COMBO_END};
const uint16_t PROGMEM pc_cut[]       = {KC_C, KC_N, COMBO_END};
const uint16_t PROGMEM pc_paste[]     = {KC_L, KC_D, COMBO_END};
const uint16_t PROGMEM pc_copypaste[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM pc_find[]      = {KC_L, KC_T, COMBO_END};
const uint16_t PROGMEM pc_clip[]      = {KC_D, KC_V, COMBO_END};

// this combo mirrors the DW action in vim!
const uint16_t PROGMEM del_word[] = {KC_W, KC_D, COMBO_END};
// keep shift+V on the left side
const uint16_t PROGMEM vimshiftv[]  = {KC_N, KC_D, COMBO_END};
const uint16_t PROGMEM slack_code[] = {KC_F, KC_M, COMBO_END};
const uint16_t PROGMEM slack_code_paste[] = {KC_F, KC_M, KC_P, COMBO_END};
// const uint16_t PROGMEM escape[]     = {KC_S, KC_M, COMBO_END};
const uint16_t PROGMEM dlsim[]      = {KC_N, KC_T, COMBO_END};
const uint16_t PROGMEM newtab[]     = {KC_T, KC_G, COMBO_END};

// RIGHT HAND
// vim combos rooted from right home row middle finger
const uint16_t PROGMEM vimwrite[]     = {KC_E, KC_A, COMBO_END};
const uint16_t PROGMEM vimwritequit[] = {KC_E, KC_U, COMBO_END};
const uint16_t PROGMEM vimquit[]      = {KC_E, KC_QUOT, COMBO_END};
const uint16_t PROGMEM vimquitall[]   = {KC_E, KC_MINS, COMBO_END};
// linux combos
const uint16_t PROGMEM lnx_cls[]  = {KC_Y, KC_O, COMBO_END};
const uint16_t PROGMEM lnx_last[] = {KC_I, KC_SLSH, COMBO_END};
const uint16_t PROGMEM ku_qu[]    = {KC_U, KC_K, COMBO_END};
const uint16_t PROGMEM at[]     = {KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM dollar[] = {KC_SLSH, KC_MINS, COMBO_END};
// . + , = ;
const uint16_t PROGMEM semicolon[]     = {KC_DOT, KC_COMM, COMBO_END};
const uint16_t PROGMEM win_bluetooth[] = {KC_K, KC_Y, COMBO_END};

combo_t key_combos[] = {
    [COMBO_VIM_WRITE]       = COMBO(vimwrite,       VIMWRITE),
    [COMBO_VIM_WRITEQUIT]   = COMBO(vimwritequit,   VIMWRITEQUIT),
    [COMBO_VIM_QUIT]        = COMBO(vimquit,        VIMQUIT),
    [COMBO_VIM_QUITALL]     = COMBO(vimquitall,     VIMQUITALL),
    [COMBO_VIM_SHIFTV]      = COMBO(vimshiftv,      S(KC_V)),
    [COMBO_PC_COPY]         = COMBO(pc_copy,        PC_COPY),
    [COMBO_PC_CUT]          = COMBO(pc_cut,         PC_CUT),
    [COMBO_PC_PASTE]        = COMBO(pc_paste,       PC_PASTE),
    [COMBO_PC_FIND]         = COMBO(pc_find,        PC_FIND),
    [COMBO_PC_UNDO]         = COMBO(pc_undo,        PC_UNDO),
    [COMBO_PC_SELECTALL]    = COMBO(pc_selectall,   PC_SALL),
    [COMBO_PC_COPYPASTE]    = COMBO(pc_copypaste,   COPY_PASTE),
    [COMBO_WIN_BLUETOOTH]   = COMBO(win_bluetooth,  G(KC_K)),
    [COMBO_LNX_LAST]        = COMBO(lnx_last,       LNX_LAST),
    [COMBO_LNX_CLS]         = COMBO(lnx_cls,        C(KC_L)),
    [COMBO_KU_QU]           = COMBO(ku_qu,          KU_QU),
    [COMBO_AT]              = COMBO(at,             KC_AT),
    [COMBO_DOLLAR]          = COMBO(dollar,         KC_DLR),
    [COMBO_SEMICOLON]       = COMBO(semicolon,      KC_SCLN),
    [COMBO_DEL_WORD]        = COMBO(del_word,       C(KC_DEL)),
    // [COMBO_ESC]             = COMBO(escape,         KC_ESC),
    [COMBO_DLSIM]           = COMBO(dlsim,          DLSIM),
    [COMBO_SLACK_CODE]      = COMBO(slack_code,     SLACK_CODE),
    [COMBO_SLACK_CODE_PASTE] = COMBO(slack_code_paste, SLACK_CODE_PASTE),
    [COMBO_NEWTAB]          = COMBO(newtab,         C(KC_T)),
    [COMBO_WIN_CLIP]        = COMBO(pc_clip,        G(KC_V)),
};

// #endif


// CUSTOM MODIFIER OVERRIDES
// shift () gives {}
const key_override_t left_paran_override  = ko_make_basic(MOD_MASK_SHIFT, KC_LPRN, KC_LCBR);
const key_override_t right_paran_override = ko_make_basic(MOD_MASK_SHIFT, KC_RPRN, KC_RCBR);
// shift [] gives <>
const key_override_t left_squarebracket_override  = ko_make_basic(MOD_MASK_SHIFT, KC_LBRC, KC_LABK);
const key_override_t right_squarebracket_override = ko_make_basic(MOD_MASK_SHIFT, KC_RBRC, KC_RABK);
// shift . gives ?
const key_override_t period_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_QUES);
// shift / gives !
const key_override_t slash_override = ko_make_basic(MOD_MASK_SHIFT, KC_SLSH, KC_EXLM);
// shift , gives :
const key_override_t comma_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_COLN);
// shift * gives #
const key_override_t asterisk_override = ko_make_basic(MOD_MASK_SHIFT, KC_PAST, KC_HASH);
// shift : gives ;
const key_override_t colon_override = ko_make_basic(MOD_MASK_SHIFT, KC_COLN, KC_SCLN);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &left_paran_override,
    &right_paran_override,
    &left_squarebracket_override,
    &right_squarebracket_override,
    &period_override,
    &slash_override,
    &comma_override,
    &asterisk_override,
    &colon_override,
    NULL // Null terminate the array of overrides!
};

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
                        case KC_X: // XM -> XL
                            tap_code(KC_L);
                            return_state = false; // done.
                    }
                    break;
                case KC_F:
                    switch (prior_keycode) {
                        case KC_X: //XF -> XC
                            tap_code(KC_C);
                            return_state = false; // done.
                    }
                    break;
                case KC_C:
                    switch (prior_keycode) {
                        case KC_L: //LC -> LF
                            tap_code(KC_F);
                            return_state = false; // done.
                    }
                    break;
                // case KC_V:
                //     switch (prior_keycode) {
                //         case KC_L: //LV -> LB
                //             tap_code(KC_B);
                //             return_state = false; // done.
                //     }
                //     break;
                // case KC_W:
                //     switch (prior_keycode) {
                //         case KC_C: //CW -> CR
                //             tap_code(KC_R);
                //             return_state = false; // done.
                //     }
                //     break;
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
                SEND_CAP_STRING("qu", "Qu");
            }
            break;
        case DLSIM:
            if (record->event.pressed) {
                SEND_CAP_STRING("dlsim", "DLSim")
            }
            break;
        case SLACK_CODE:
            if (record->event.pressed) {
                SEND_STRING("```");
            }
            break;
        case SLACK_CODE_PASTE:
            if (record->event.pressed) {
                SEND_STRING("```" SS_DELAY(100) SS_LCTL(SS_TAP(X_V)));
            }
            break;
        case COPY_PASTE:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_C)) SS_DELAY(100) SS_LCTL(SS_TAP(X_V)));
            }
            break;
        case IMPORT_PDB:
            if (record->event.pressed) {
                SEND_STRING("import pdb; pdb.set_trace()");
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
        case _NAV_NUM_SYM:
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
        case _NAV_NUM_SYM:
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
//     rgblight_set_layer_state(3, layer_state_cmp(state, _NAV_NUM_SYM));
//     return state;
// }

// Runs just one time when the keyboard initializes.
void matrix_scan_user(void) {
    static bool has_ran_yet = false;
    if (!has_ran_yet) {
        has_ran_yet = true;
        // rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 3);
        // rgblight_mode(RGBLIGHT_MODE_BREATHING + 1);
        // rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
        // rgblight_sethsv(HSV_WHITE);
    }
    if (is_alt_tab_active) {
      if (timer_elapsed(alt_tab_timer) > 1000) {
        unregister_code(KC_LALT);
        is_alt_tab_active = false;
      }
    }
};


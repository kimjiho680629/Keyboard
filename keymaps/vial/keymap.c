#include QMK_KEYBOARD_H

// 1. 커스텀 키코드 정의 (Vial QK_KB_0 ~ QK_KB_4)
enum custom_keycodes {
    GAME_345     = QK_KB_0, // Vial User 0 (345 연타)
    GAME_2345    = QK_KB_1, // Vial User 1 (2345 연타)
    GAME_12345   = QK_KB_2, // Vial User 2 (12345 연타)
    GAME_45      = QK_KB_3, // Vial User 3 (45 연타)
    GAME_L_MOUSE = QK_KB_4, // Vial User 4 (마우스 좌클릭 50ms 최적 연타)
};

// 2. 키맵 (silakka54.vil 기준 기본 레이아웃)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        QK_GESC,      KC_1,    KC_2,    KC_3,    KC_4,          KC_5,           KC_6,     KC_7,    KC_8,     KC_9,       KC_0,        TD(1),
        LT(3, KC_TAB),KC_Q,    KC_W,    KC_E,    KC_R,          KC_T,           KC_Y,     KC_U,    KC_I,     KC_O,       KC_P,        KC_BSPC,
        TD(0),        KC_A,    KC_S,    KC_D,    KC_F,          KC_G,           KC_H,     KC_J,    KC_K,     KC_L,       KC_SCLN,     KC_QUOT,
        KC_LSFT,      KC_Z,    KC_X,    KC_C,    KC_V,          KC_B,           KC_N,     KC_M,    KC_COMM,  KC_DOT,     KC_SLSH,     KC_RSFT,
        KC_LGUI,      MO(1),   LT(2, KC_SPC),                                   KC_ENT,   KC_LCTL, KC_LALT
    ),
    [1] = LAYOUT(
        LSFT(KC_GRV), KC_F1,   KC_F2,   KC_F3,   KC_F4,         GAME_L_MOUSE,   KC_F6,    KC_F7,   KC_F8,    KC_F9,      KC_F10,      KC_F11,
        KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,        KC_PGUP,  KC_PGDN, KC_HOME,  KC_END,     KC_BSLS,     KC_F12,
        KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,        KC_LEFT,  KC_DOWN, KC_UP,    KC_RGHT,    KC_LBRC,     KC_RBRC,
        KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,        KC_TRNS,  KC_TRNS, KC_VOLD,  KC_VOLU,    KC_TRNS,     KC_DEL,
        KC_TRNS,      KC_TRNS, KC_TRNS,                                         KC_TRNS,  KC_RCTL, KC_RALT
    ),
    [2] = LAYOUT(
        KC_TRNS,      GAME_45, GAME_L_MOUSE, KC_TRNS, KC_TRNS,  KC_TRNS,        KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,     KC_TRNS,
        KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,        KC_PGDN,  KC_PGUP, KC_HOME,  KC_END,     KC_TRNS,     KC_TRNS,
        KC_TRNS,      KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,        KC_WBAK,  KC_WHOM, KC_WREF,  KC_WFWD,    KC_TRNS,     KC_TRNS,
        KC_LEFT,      KC_DOWN, KC_RGHT, C(S(KC_C)), C(S(KC_V)), KC_TRNS,        KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,     KC_TRNS,
        KC_TRNS,      KC_TRNS, KC_TRNS,                                         KC_TRNS,  KC_TRNS, KC_TRNS
    ),
    [3] = LAYOUT(
        KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,        KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,     KC_PWR,
        KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,        KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,     KC_TRNS,
        KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,        KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,     KC_TRNS,
        KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,        KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,     KC_TRNS,
        KC_TRNS,      KC_TRNS, KC_TRNS,                                         KC_TRNS,  KC_TRNS, KC_TRNS
    )
};


// 3. RGB LED 레이어 설정
#ifdef RGBLIGHT_ENABLE

#define HSV_BROWN 28, 255, 128

const rgblight_segment_t PROGMEM my_layer1_layer[]    = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_BLUE});
const rgblight_segment_t PROGMEM my_layer2_layer[]    = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_GREEN});
const rgblight_segment_t PROGMEM my_layer3_layer[]    = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_PURPLE});
const rgblight_segment_t PROGMEM my_gui_layer[]       = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_PINK});
const rgblight_segment_t PROGMEM my_capslock_layer[]  = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_YELLOW});
const rgblight_segment_t PROGMEM my_game345_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_ORANGE});  // 345: 주황
const rgblight_segment_t PROGMEM my_game2345_layer[]  = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_BROWN});   // 2345: 브라운
const rgblight_segment_t PROGMEM my_game12345_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_CYAN});    // 12345: 하늘색
const rgblight_segment_t PROGMEM my_game45_layer[]    = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_RED});     // 45: 빨강
const rgblight_segment_t PROGMEM my_gamelmouse_layer[]= RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_MAGENTA}); // 마우스: 자홍색

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer1_layer,    // 0
    my_layer2_layer,    // 1
    my_layer3_layer,    // 2
    my_gui_layer,       // 3
    my_capslock_layer,  // 4
    my_game345_layer,   // 5
    my_game2345_layer,  // 6
    my_game12345_layer, // 7
    my_game45_layer,    // 8
    my_gamelmouse_layer // 9 (최우선)
);

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
    rgblight_sethsv_noeeprom(HSV_WHITE);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(4, led_state.caps_lock);
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);
    rgblight_set_layer_state(0, false);
    rgblight_set_layer_state(1, false);
    rgblight_set_layer_state(2, false);

    switch (layer) {
        case 1: rgblight_set_layer_state(0, true); break;
        case 2: rgblight_set_layer_state(1, true); break;
        case 3: rgblight_set_layer_state(2, true); break;
        default: break;
    }
    return state;
}
#endif

// 4. 게임 토글 타이머 변수 및 순환 시퀀스
static bool game345_on     = false;
static bool game2345_on    = false;
static bool game12345_on   = false;
static bool game45_on      = false;
static bool gamelmouse_on  = false;

static uint16_t game345_timer    = 0;
static uint16_t game2345_timer   = 0;
static uint16_t game12345_timer  = 0;
static uint16_t game45_timer     = 0;
static uint16_t gamelmouse_timer = 0;

static uint8_t seq_idx_345   = 0;
static uint8_t seq_idx_2345  = 0;
static uint8_t seq_idx_12345 = 0;
static uint8_t seq_idx_45    = 0;

static const uint16_t seq_345[]   = {KC_3, KC_4, KC_5};
static const uint16_t seq_2345[]  = {KC_2, KC_3, KC_4, KC_5};
static const uint16_t seq_12345[] = {KC_1, KC_2, KC_3, KC_4, KC_5};
static const uint16_t seq_45[]    = {KC_4, KC_5};

static inline void tap_fast(uint16_t keycode) {
    register_code16(keycode);
    unregister_code16(keycode);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LGUI:
        case KC_RGUI:
            #ifdef RGBLIGHT_ENABLE
            rgblight_set_layer_state(3, record->event.pressed);
            #endif
            return true;
        case LGUI_T(KC_D):
        case RGUI_T(KC_K):
            if (record->tap.count == 0) {
                #ifdef RGBLIGHT_ENABLE
                rgblight_set_layer_state(3, record->event.pressed);
                #endif
            }
            return true;

        // GAME_345 (주황)
        case GAME_345:
            if (record->event.pressed) {
                game345_on = !game345_on;
                #ifdef RGBLIGHT_ENABLE
                rgblight_set_layer_state(5, game345_on);
                #endif
                seq_idx_345 = 0;
                if (game345_on) {
                    game345_timer = timer_read();
                } else {
                    unregister_code16(KC_3);
                    unregister_code16(KC_4);
                    unregister_code16(KC_5);
                }
            }
            return false;

        // GAME_2345 (브라운)
        case GAME_2345:
            if (record->event.pressed) {
                game2345_on = !game2345_on;
                #ifdef RGBLIGHT_ENABLE
                rgblight_set_layer_state(6, game2345_on);
                #endif
                seq_idx_2345 = 0;
                if (game2345_on) {
                    game2345_timer = timer_read();
                } else {
                    unregister_code16(KC_2);
                    unregister_code16(KC_3);
                    unregister_code16(KC_4);
                    unregister_code16(KC_5);
                }
            }
            return false;

        // GAME_12345 (하늘색)
        case GAME_12345:
            if (record->event.pressed) {
                game12345_on = !game12345_on;
                #ifdef RGBLIGHT_ENABLE
                rgblight_set_layer_state(7, game12345_on);
                #endif
                seq_idx_12345 = 0;
                if (game12345_on) {
                    game12345_timer = timer_read();
                } else {
                    unregister_code16(KC_1);
                    unregister_code16(KC_2);
                    unregister_code16(KC_3);
                    unregister_code16(KC_4);
                    unregister_code16(KC_5);
                }
            }
            return false;

        // GAME_45 (빨강)
        case GAME_45:
            if (record->event.pressed) {
                game45_on = !game45_on;
                #ifdef RGBLIGHT_ENABLE
                rgblight_set_layer_state(8, game45_on);
                #endif
                seq_idx_45 = 0;
                if (game45_on) {
                    game45_timer = timer_read();
                } else {
                    unregister_code16(KC_4);
                    unregister_code16(KC_5);
                }
            }
            return false;

        // GAME_L_MOUSE (자홍색, 마우스 50ms 디아블로4 최적 연타)
        case GAME_L_MOUSE:
            if (record->event.pressed) {
                gamelmouse_on = !gamelmouse_on;
                #ifdef RGBLIGHT_ENABLE
                rgblight_set_layer_state(9, gamelmouse_on);
                #endif
                if (gamelmouse_on) {
                    gamelmouse_timer = timer_read();
                } else {
                    unregister_code16(KC_MS_BTN1);
                }
            }
            return false;
    }
    return true;
}

void matrix_scan_user(void) {
    #ifdef RGBLIGHT_ENABLE
    if (host_keyboard_led_state().caps_lock) {
        rgblight_set_layer_state(4, true);
    } else {
        rgblight_set_layer_state(4, false);
    }
    #endif

    // 345 순환 틱 무지연 연타 (25ms마다 순차 1키 전송 -> OS 버퍼링 제로)
    if (game345_on && timer_elapsed(game345_timer) >= 25) {
        game345_timer = timer_read();
        tap_fast(seq_345[seq_idx_345]);
        seq_idx_345 = (seq_idx_345 + 1) % 3;
    }

    // 2345 순환 틱 무지연 연타 (25ms마다 순차 1키 전송)
    if (game2345_on && timer_elapsed(game2345_timer) >= 25) {
        game2345_timer = timer_read();
        tap_fast(seq_2345[seq_idx_2345]);
        seq_idx_2345 = (seq_idx_2345 + 1) % 4;
    }

    // 12345 순환 틱 무지연 연타 (25ms마다 순차 1키 전송)
    if (game12345_on && timer_elapsed(game12345_timer) >= 25) {
        game12345_timer = timer_read();
        tap_fast(seq_12345[seq_idx_12345]);
        seq_idx_12345 = (seq_idx_12345 + 1) % 5;
    }

    // 45 순환 틱 무지연 연타 (25ms마다 순차 1키 전송)
    if (game45_on && timer_elapsed(game45_timer) >= 25) {
        game45_timer = timer_read();
        tap_fast(seq_45[seq_idx_45]);
        seq_idx_45 = (seq_idx_45 + 1) % 2;
    }

    // 마우스 좌클릭 50ms 무지연 논블로킹 연타 (디아블로4 루팅 최적 속도: 초당 20회)
    if (gamelmouse_on && timer_elapsed(gamelmouse_timer) >= 50) {
        gamelmouse_timer = timer_read();
        tap_fast(KC_MS_BTN1);
    }
}



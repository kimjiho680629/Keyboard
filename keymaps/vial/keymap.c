#include QMK_KEYBOARD_H

// 1. 커스텀 키코드 정의 (Vial QK_KB_0 ~ QK_KB_4)
enum custom_keycodes {
    GAME_345     = QK_KB_0, // Vial User 0 (345 연타)
    GAME_2345    = QK_KB_1, // Vial User 1 (2345 연타)
    GAME_12345   = QK_KB_2, // Vial User 2 (12345 연타)
    GAME_45      = QK_KB_3, // Vial User 3 (45 연타)
    GAME_L_MOUSE = QK_KB_4, // Vial User 4 (마우스 좌클릭 50ms 최적 연타)
};

// 2. 키맵 (기본 레이아웃 및 커스텀 키 배치)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS,
        TG(2),  KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC,
        KC_TAB, LCTL_T(KC_A), LALT_T(KC_S), LGUI_T(KC_D), LSFT_T(KC_F), KC_G, KC_H, RSFT_T(KC_J), RGUI_T(KC_K), RALT_T(KC_L), RCTL_T(KC_SCLN), KC_QUOT,
        TG(1),  KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, TG(3),
        KC_NO,  KC_BSPC, KC_SPC, KC_ENT, KC_DEL, KC_RALT
    ),
    [1] = LAYOUT(
        KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
        KC_TRNS, GAME_12345, GAME_45, GAME_L_MOUSE, KC_NO, KC_NO, KC_PGUP, KC_PGDN, KC_HOME, KC_END, KC_DEL, GAME_345,
        KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_LBRC, KC_RBRC,
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, GAME_2345, KC_NO, KC_NO, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [2] = LAYOUT(
        KC_BRID, KC_BRIU, KC_VOLD, KC_VOLU, KC_MUTE, KC_FIND, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, MS_WHLU, MS_UP, MS_WHLD, KC_NO, KC_NO,
        KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   MS_WHLL, MS_LEFT, MS_DOWN, MS_RGHT, MS_WHLR, KC_NO,
        KC_TRNS, KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   MS_BTN3, MS_BTN4, MS_BTN5, KC_NO, KC_NO, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, MS_BTN1, MS_BTN2, KC_NO
    ),
    [3] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RALT(KC_1), RSFT(KC_2), KC_MINS, KC_NO, KC_NO, KC_NO,
        KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LSFT(KC_8), LSFT(KC_9), RALT(KC_QUOT), RALT(KC_NUHS), RALT(KC_SCLN), KC_NO,
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NUBS, LSFT(KC_NUBS), LSFT(KC_COMM), LSFT(KC_DOT), KC_NO, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
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

// 4. 게임 토글 타이머 변수
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
                if (game345_on) game345_timer = timer_read();
            }
            return false;

        // GAME_2345 (브라운)
        case GAME_2345:
            if (record->event.pressed) {
                game2345_on = !game2345_on;
                #ifdef RGBLIGHT_ENABLE
                rgblight_set_layer_state(6, game2345_on);
                #endif
                if (game2345_on) game2345_timer = timer_read();
            }
            return false;

        // GAME_12345 (하늘색)
        case GAME_12345:
            if (record->event.pressed) {
                game12345_on = !game12345_on;
                #ifdef RGBLIGHT_ENABLE
                rgblight_set_layer_state(7, game12345_on);
                #endif
                if (game12345_on) game12345_timer = timer_read();
            }
            return false;

        // GAME_45 (빨강)
        case GAME_45:
            if (record->event.pressed) {
                game45_on = !game45_on;
                #ifdef RGBLIGHT_ENABLE
                rgblight_set_layer_state(8, game45_on);
                #endif
                if (game45_on) game45_timer = timer_read();
            }
            return false;

        // GAME_L_MOUSE (자홍색, 마우스 50ms 디아블로4 최적 연타)
        case GAME_L_MOUSE:
            if (record->event.pressed) {
                gamelmouse_on = !gamelmouse_on;
                #ifdef RGBLIGHT_ENABLE
                rgblight_set_layer_state(9, gamelmouse_on);
                #endif
                if (gamelmouse_on) gamelmouse_timer = timer_read();
            }
            return false;
    }
    return true;
}

static inline void tap_fast(uint16_t keycode) {
    register_code16(keycode);
    unregister_code16(keycode);
}

void matrix_scan_user(void) {
    #ifdef RGBLIGHT_ENABLE
    if (host_keyboard_led_state().caps_lock) {
        rgblight_set_layer_state(4, true);
    } else {
        rgblight_set_layer_state(4, false);
    }
    #endif

    // 345 25ms 무지연 논블로킹 연타
    if (game345_on && timer_elapsed(game345_timer) >= 25) {
        game345_timer = timer_read();
        tap_fast(KC_3);
        tap_fast(KC_4);
        tap_fast(KC_5);
    }

    // 2345 25ms 무지연 논블로킹 연타
    if (game2345_on && timer_elapsed(game2345_timer) >= 25) {
        game2345_timer = timer_read();
        tap_fast(KC_2);
        tap_fast(KC_3);
        tap_fast(KC_4);
        tap_fast(KC_5);
    }

    // 12345 25ms 무지연 논블로킹 연타
    if (game12345_on && timer_elapsed(game12345_timer) >= 25) {
        game12345_timer = timer_read();
        tap_fast(KC_1);
        tap_fast(KC_2);
        tap_fast(KC_3);
        tap_fast(KC_4);
        tap_fast(KC_5);
    }

    // 45 25ms 무지연 논블로킹 연타
    if (game45_on && timer_elapsed(game45_timer) >= 25) {
        game45_timer = timer_read();
        tap_fast(KC_4);
        tap_fast(KC_5);
    }

    // 마우스 좌클릭 50ms 무지연 논블로킹 연타 (디아블로4 루팅 최적 속도: 초당 20회)
    if (gamelmouse_on && timer_elapsed(gamelmouse_timer) >= 50) {
        gamelmouse_timer = timer_read();
        tap_fast(KC_MS_BTN1);
    }
}


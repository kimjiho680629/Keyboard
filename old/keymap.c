#include QMK_KEYBOARD_H

// 1. 커스텀 키코드 정의
enum custom_keycodes {
    GAME_345  = QK_KB_0, // Vial User 0
    GAME_2345 = QK_KB_1, // Vial User 1
};

// 2. 키맵 (원본 레이아웃 유지)
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
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PGUP, KC_PGDN, KC_HOME, KC_END, KC_DEL, GAME_345,
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

// 3. LED 설정
#ifdef RGBLIGHT_ENABLE

// [색상 정의]
// HSV_BROWN 정의 (갈색 느낌: Hue=28, Sat=255, Val=100~200)
#define HSV_BROWN 28, 255, 128

const rgblight_segment_t PROGMEM my_layer1_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_BLUE});
const rgblight_segment_t PROGMEM my_layer2_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_GREEN});
const rgblight_segment_t PROGMEM my_layer3_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_PURPLE});
const rgblight_segment_t PROGMEM my_gui_layer[]      = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_PINK});
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_YELLOW});
const rgblight_segment_t PROGMEM my_game345_layer[]  = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_ORANGE}); // 345: 주황
const rgblight_segment_t PROGMEM my_game2345_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_BROWN});  // 2345: 브라운

// [우선순위 리스트]
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer1_layer,   // 0
    my_layer2_layer,   // 1
    my_layer3_layer,   // 2
    my_gui_layer,      // 3
    my_capslock_layer, // 4
    my_game345_layer,  // 5 (345 켜지면 주황)
    my_game2345_layer  // 6 (2345 켜지면 브라운 - 최우선)
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

// 4. 게임키 & GUI키 로직
static bool game345_on  = false;
static bool game2345_on = false;
static uint16_t game345_timer  = 0;
static uint16_t game2345_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // GUI 키
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
                rgblight_set_layer_state(5, game345_on); // 레이어 5
                #endif
                if (game345_on) game345_timer = timer_read();
            }
            return false;

        // GAME_2345 (브라운)
        case GAME_2345:
            if (record->event.pressed) {
                game2345_on = !game2345_on;
                #ifdef RGBLIGHT_ENABLE
                rgblight_set_layer_state(6, game2345_on); // 레이어 6 (최우선)
                #endif
                if (game2345_on) game2345_timer = timer_read();
            }
            return false;
    }
    return true;
}

void matrix_scan_user(void) {
    // Caps Lock 상태 강제 확인
    #ifdef RGBLIGHT_ENABLE
    if (host_keyboard_led_state().caps_lock) {
        rgblight_set_layer_state(4, true);
    } else {
        rgblight_set_layer_state(4, false);
    }
    #endif

    // 매크로 실행
    if (game345_on && timer_elapsed(game345_timer) > 25) {
        game345_timer = timer_read();
        SEND_STRING("345");
    }
    if (game2345_on && timer_elapsed(game2345_timer) > 25) {
        game2345_timer = timer_read();
        SEND_STRING("2345");
    }
}


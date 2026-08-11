# ⌨️ Silakka54 Custom Keymap & Firmware 작업 기록 보고서

> **작성 일시**: 2026-08-11  
> **대상 기기**: Silakka54 (54-key RP2040 Split Keyboard)  
> **목적**: 커스텀 User 연타 매크로 키 확장, RGB Indicator 레이어 구현 및 QMK/Vial 펌웨어 빌드 환경 정리

---

## 1. 📌 프로젝트 개요 및 현재 구조

이 작업 공간은 **Silakka54 분할 키보드**의 Vial GUI 레이아웃 백업(`.vil`)과 QMK C 소스코드 커스텀 펌웨어 빌드 환경을 관리합니다.

```
silakka54_keymap/
├── silakka54.vil        # Vial GUI용 백업 레이아웃 파일
├── WORK_LOG.md          # [본 문서] 진행 상황 및 기술 명세서
├── old/                 # 이전 원본 소스코드 백업 폴더
│   ├── config.h
│   ├── keymap.c
│   ├── rules.mk
│   ├── vial.json
│   └── silakka54_vial.uf2 # 검증된 RP2040 플래싱 펌웨어 바이너리
├── vial-qmk/            # 최신 QMK/Vial 펌웨어 소스 레포지토리
│   └── keyboards/silakka54/keymaps/vial/ # 커스텀 펌웨어 소스 트리
│       ├── config.h
│       ├── keymap.c
│       ├── rules.mk
│       └── vial.json
├── firmware/            # 빌드된 최신 .uf2 결과물 보관 폴더
└── scripts/             # 컴파일 및 툴체인 자동화 스크립트
    ├── setup_compiler.sh
    └── build_firmware.sh
```

---

## 2. 🎮 추가/구현된 커스텀 User 키 5종 사양

QMK의 `matrix_scan_user()`와 타이머(`timer_elapsed()`)를 활용하여 입력 딜레이 없는 **Non-blocking 지속 연타 기능**과 **RGB Indicator LED**를 통합 구현했습니다.

| 키코드 (C Enum) | Vial 표시명 | Keycode ID | 동작 방식 및 사양 | RGB LED 인디케이터 |
| :--- | :--- | :--- | :--- | :--- |
| **`GAME_345`** | `GM345` | `QK_KB_0` (0x7E40) | **`"345"` 25ms 간격 지속 연타** (토글) | 🟧 **주황색 (`HSV_ORANGE`)** |
| **`GAME_2345`** | `GM2345` | `QK_KB_1` (0x7E41) | **`"2345"` 25ms 간격 지속 연타** (토글) | 🟫 **브라운 (`HSV_BROWN`)** |
| **`GAME_12345`** | `GM12345` | `QK_KB_2` (0x7E42) | **`"12345"` 25ms 간격 지속 연타** (토글) | 🩵 **하늘색 (`HSV_CYAN`)** |
| **`GAME_45`** | `GM45` | `QK_KB_3` (0x7E43) | **`"45"` 25ms 간격 지속 연타** (토글) | 🔴 **빨간색 (`HSV_RED`)** |
| **`GAME_L_MOUSE`** | `GMLMS` | `QK_KB_4` (0x7E44) | **마우스 좌클릭 20ms 간격 초고속 연타** (토글) | 🩷 **자홍색 (`HSV_MAGENTA`)** |

---

## 3. 🗺️ 기존 키맵 레이아웃 요약 (`silakka54.vil` & `keymap.c`)

### 🟢 Layer 0 (기본 레이어)
* **Left**: `GESC`, `1~5`, `Q~T`, `A~G`, `Z~B`, `Tab(Hold: L3)`, `TD(0)`
* **Right**: `TD(1)`, `0~6`, `P~Y`, `Quote~H`, `Slash~N`, `Backspace`
* **Thumbs**: Left (`LGUI`, `MO(1)`, `Space(Hold: L2)`) / Right (`LAlt`, `LCtrl`, `Enter`)
* **Tap Dance**:
  * `TD(0)`: Tap = **한/영 (LANG1)** / Double Tap = **Caps Lock**
  * `TD(1)`: Tap = **`-`** / Double Tap = **`=`**

### 🔵 Layer 1 (기능키, 특수문자 & 커스텀 키)
* **Row 0**: `~`, `F1`~`F4`, `M5(오토클릭)` / `F11`~`F6`
* **Row 1**: *(Left)* `GAME_12345`, `GAME_45`, `GAME_L_MOUSE` 배치 / *(Right)* `F12`, `\`, `End`, `Home`, `PgDn`, `PgUp`, `GAME_345`
* **Row 2**: 방향키 (`Left`, `Down`, `Up`, `Right`), `[`, `]`
* **Row 3**: `Delete`, `Vol+`, `Vol-`, `GAME_2345`

### 🟣 Layer 2 (마우스/이동 레이어)
* 방향키 네비게이션, 마우스 휠(`MS_WHLU`, `MS_WHLD`), 마우스 버튼(`MS_BTN1`~`5`)

---

## 4. 📝 주요 파일 수정 내역

### 1) [`vial-qmk/keyboards/silakka54/keymaps/vial/keymap.c`](file:///home/kjh/Projects/Gemini_Job/silakka54_keymap/vial-qmk/keyboards/silakka54/keymaps/vial/keymap.c)
* `QK_KB_0` ~ `QK_KB_4` 사용자 정의 키코드 추가
* `process_record_user()`에서 각 토글 키 누름 감지 및 RGB Layer 활성화
* `matrix_scan_user()`에서 `timer_elapsed()` 25ms/20ms 타이머 체킹 및 `SEND_STRING()` / `tap_code(KC_MS_BTN1)` 호출
* RGB Indicator Layer Segment 10개 정의 (Caps Lock, Layer 1~3, GUI, GAME 키 5종)

### 2) [`vial-qmk/keyboards/silakka54/keymaps/vial/vial.json`](file:///home/kjh/Projects/Gemini_Job/silakka54_keymap/vial-qmk/keyboards/silakka54/keymaps/vial/vial.json)
* Vial GUI 앱의 "Custom Keycodes" 탭에 `GM345`, `GM2345`, `GM12345`, `GM45`, `GMLMS` 등록

### 3) [`vial-qmk/keyboards/silakka54/keymaps/vial/config.h`](file:///home/kjh/Projects/Gemini_Job/silakka54_keymap/vial-qmk/keyboards/silakka54/keymaps/vial/config.h)
* `#define RGBLIGHT_MAX_LAYERS 16` (RGB 레이어 메모리 확보)
* `#define SPLIT_LED_STATE_ENABLE`, `#define RGBLIGHT_SPLIT` (스플릿 동기화)

### 4) [`vial-qmk/keyboards/silakka54/keymaps/vial/rules.mk`](file:///home/kjh/Projects/Gemini_Job/silakka54_keymap/vial-qmk/keyboards/silakka54/keymaps/vial/rules.mk)
* `MOUSEKEY_ENABLE = yes` (마우스 버튼 클릭 제어)

---

## 5. 🚀 추후 이어서 진행하는 가이드 (Next Steps)

### 1) 펌웨어 컴파일 및 실물 키보드 플래싱
이후 빌드나 플래싱 작업을 진행하실 때는 터미널에서 아래 스크립트를 실행하시면 됩니다:

```bash
# 1. 툴체인 패키지 확인 및 설치 (최초 1회)
./scripts/setup_compiler.sh

# 2. 최신 .uf2 펌웨어 파일 빌드
./scripts/build_firmware.sh
```
* 컴파일된 결과물은 `./firmware/silakka54_vial_YYYYMMDD_HHMMSS.uf2` 파일로 자동 보관됩니다.
* 키보드의 **BOOT 버튼**을 누른 상태로 PC에 연결하여 `RPI-RP2` 드라이브가 뜨면 해당 `.uf2` 파일을 복사해 넣으면 완료됩니다.

### 2) 추가 커스텀 키 확장이 필요한 경우
1. [`keymap.c`](file:///home/kjh/Projects/Gemini_Job/silakka54_keymap/vial-qmk/keyboards/silakka54/keymaps/vial/keymap.c)의 `custom_keycodes` enum에 `USER_NEW = QK_KB_5` 형태로 추가
2. `process_record_user` 및 `matrix_scan_user`에 타이머/연타 logic과 RGB layer 지정
3. [`vial.json`](file:///home/kjh/Projects/Gemini_Job/silakka54_keymap/vial-qmk/keyboards/silakka54/keymaps/vial/vial.json)의 `customKeycodes`에 이름 및 `0x7E45` 키코드 등록

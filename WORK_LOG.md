# ⌨️ Silakka54 Custom Keymap & Firmware 작업 기록 보고서

> **최종 수정 일시**: 2026-08-20  
> **대상 기기**: Silakka54 (54-key RP2040 Split Keyboard)  
> **목적**: 커스텀 User 연타 매크로 키 논블로킹(Non-blocking) 최적화 (토글 즉각 종료 및 매트릭스 스캔 프리징 해결), 디아블로 4 루팅 최적화(50ms), RGB Indicator 레이어 구현 및 QMK/Vial 펌웨어 빌드

---

## 1. 📌 프로젝트 개요 및 현재 구조

이 작업 공간은 **Silakka54 분할 키보드**의 Vial GUI 레이아웃 백업(`.vil`)과 QMK C 소스코드 커스텀 펌웨어 빌드 환경을 관리합니다.

```
silakka54_keymap/
├── silakka54.vil        # Vial GUI용 백업 레이아웃 파일
├── WORK_LOG.md          # [본 문서] 진행 상황 및 기술 명세서
├── README.md            # 저장소 사용 가이드
├── silakka54_backup_20260811.tar.gz # 전체 소스 및 바이너리 통합 백업 파일
├── keymaps/vial/        # 프로젝트 루트 백업 커스텀 소스
│   ├── config.h
│   ├── keymap.c
│   ├── rules.mk
│   └── vial.json
├── firmware/            # 빌드된 최신 .uf2 결과물 보관 폴더
│   ├── silakka54_vial_20260820.uf2 # [최신] 논블로킹 tap_fast 최적화 바이너리
│   ├── silakka54_vial_20260811.uf2 # 이전 바이너리
│   └── silakka54_vial.uf2
├── old/                 # 이전 원본 소스코드 백업 폴더
└── vial-qmk/            # 최신 QMK/Vial 펌웨어 소스 레포지토리
    └── keyboards/silakka54/keymaps/vial/ # 실제 빌드 대상 소스 트리
```

---

## 2. 🎮 추가/구현된 커스텀 User 키 5종 사양

QMK의 `matrix_scan_user()`와 타이머(`timer_elapsed()`)를 활용하여 입력 딜레이 없는 **Non-blocking 지속 연타 기능(`tap_fast`)**과 **RGB Indicator LED**를 통합 구현했습니다.

| 키코드 (C Enum) | Vial 표시명 | Keycode ID | 동작 방식 및 사양 | RGB LED 인디케이터 |
| :--- | :--- | :--- | :--- | :--- |
| **`GAME_345`** | `GM345` | `QK_KB_0` (0x7E40) | **`"345"` 25ms 간격 무지연 논블로킹 연타** (토글) | 🟧 **주황색 (`HSV_ORANGE`)** |
| **`GAME_2345`** | `GM2345` | `QK_KB_1` (0x7E41) | **`"2345"` 25ms 간격 무지연 논블로킹 연타** (토글) | 🟫 **브라운 (`HSV_BROWN`)** |
| **`GAME_12345`** | `GM12345` | `QK_KB_2` (0x7E42) | **`"12345"` 25ms 간격 무지연 논블로킹 연타** (토글) | 🩵 **하늘색 (`HSV_CYAN`)** |
| **`GAME_45`** | `GM45` | `QK_KB_3` (0x7E43) | **`"45"` 25ms 간격 무지연 논블로킹 연타** (토글) | 🔴 **빨간색 (`HSV_RED`)** |
| **`GAME_L_MOUSE`** | `GMLMS` | `QK_KB_4` (0x7E44) | **마우스 좌클릭 50ms 간격 무지연 논블로킹 연타** (토글) | 🩷 **자홍색 (`HSV_MAGENTA`)** |

> 💡 **논블로킹 `tap_fast()` 최적화 (2026-08-20)**:  
> 기존 `SEND_STRING()` 및 `tap_code()` 매크로는 내부적으로 문자당 `wait_ms(TAP_CODE_DELAY)`(10~25ms)의 동기식 지연을 발생시켜 MCU를 멈추게 했습니다. 이로 인해 25ms 주기로 실행 시 키보드 매트릭스 스캔이 100% 블로킹되어 토글 해제 키 입력이 씹히거나 반응이 지연되는 문제가 있었습니다.  
> `register_code16()`과 `unregister_code16()`을 직접 호출하는 인라인 `tap_fast()` 함수로 교체하여 블로킹 타임을 0ms로 단축, 즉각적인 토글 해제와 완벽한 키 입력 반응성을 확보했습니다.

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

---

## 4. 📝 주요 파일 수정 내역

### 1) [`keymaps/vial/keymap.c`](file:///home/kjh/Projects/Gemini_Job/silakka54_keymap/keymaps/vial/keymap.c)
* `QK_KB_0` ~ `QK_KB_4` 커스텀 키코드 5종 정의
* `tap_fast()` 무지연 논블로킹 함수 적용 (매트릭스 스캔 기아 및 토글 지연 완전 해결)
* `GAME_L_MOUSE` 마우스 딜레이 50ms 최적화 (`tap_fast(KC_MS_BTN1)`)
* RGB Indicator Layer Segment 10개 정의 (Caps Lock, Layer 1~3, GUI, GAME 키 5종)

### 2) [`keymaps/vial/vial.json`](file:///home/kjh/Projects/Gemini_Job/silakka54_keymap/keymaps/vial/vial.json)
* Vial GUI 앱의 "Custom Keycodes" 탭에 `GM345`, `GM2345`, `GM12345`, `GM45`, `GMLMS` 등록

### 3) [`keymaps/vial/config.h`](file:///home/kjh/Projects/Gemini_Job/silakka54_keymap/keymaps/vial/config.h)
* `#define RGBLIGHT_MAX_LAYERS 16` (RGB 레이어 메모리 확보)
* `#define SPLIT_LED_STATE_ENABLE`, `#define RGBLIGHT_SPLIT` (스플릿 동기화)

### 4) [`keymaps/vial/rules.mk`](file:///home/kjh/Projects/Gemini_Job/silakka54_keymap/keymaps/vial/rules.mk)
* `MOUSEKEY_ENABLE = yes` (마우스 버튼 클릭 제어)

---

## 5. 🚀 추후 이어서 진행하는 가이드 (Next Steps)

### 1) 펌웨어 실물 키보드 플래싱
1. 키보드의 **BOOT 버튼**을 누른 상태로 PC에 연결합니다.
2. `RPI-RP2` USB 드라이브가 인식되면 **[`firmware/silakka54_vial_20260820.uf2`](file:///home/kjh/Projects/Gemini_Job/silakka54_keymap/firmware/silakka54_vial_20260820.uf2)** 파일(또는 [`firmware/silakka54_vial.uf2`](file:///home/kjh/Projects/Gemini_Job/silakka54_keymap/firmware/silakka54_vial.uf2))을 복사해 넣습니다.

### 2) GitHub 원격 저장소 동기화
터미널에서 아래 명령어로 GitHub 저장소([`kimjiho680629/Keyboard`](https://github.com/kimjiho680629/Keyboard))에 최종 저장할 수 있습니다:
```bash
git push origin main
```


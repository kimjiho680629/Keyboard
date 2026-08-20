# ⌨️ Silakka54 Custom Keymap & Firmware Project Guide

이 문서는 **Silakka54 (RP2040 Split Keyboard)** 커스텀 QMK/Vial 펌웨어 및 키맵 프로젝트의 구조, 설계 원리, 빌드 및 배포 절차를 정리한 레퍼런스 문서입니다.

---

## 1. 📌 프로젝트 개요

- **하드웨어**: Silakka54 (54-key RP2040 MCU 기반 분할형 키보드)
- **펌웨어 베이스**: [Vial-QMK](https://github.com/vial-kb/vial-qmk) (QMK 기반 실시간 GUI 키맵 설정 지원)
- **주요 기능**:
  - 5종 커스텀 게임/마우스 지속 연타 키 (`QK_KB_0` ~ `QK_KB_4`)
  - **Round-Robin State Machine** 기반 무지연 논블로킹(`tap_fast`) 전송 (OS 입력 버퍼 지연 0% 및 즉각 토글 해제)
  - 디아블로 4 최적화 마우스 좌클릭 연타 (50ms)
  - 다중 RGB 인디케이터 레이어 동기화 (기능별/모드별 단독 색상 피드백)

---

## 2. 🎮 커스텀 User 연타 키코드 사양

| 키코드 (C Enum) | Vial 표시명 | Keycode ID | 동작 방식 및 사양 | RGB LED 인디케이터 |
| :--- | :--- | :--- | :--- | :--- |
| **`GAME_345`** | `GM345` | `QK_KB_0` (0x7E40) | **`"345"` 순환 틱(25ms당 1키) 무지연 연타** (토글) | 🟧 **주황색 (`HSV_ORANGE`)** |
| **`GAME_2345`** | `GM2345` | `QK_KB_1` (0x7E41) | **`"2345"` 순환 틱(25ms당 1키) 무지연 연타** (토글) | 🟫 **브라운 (`HSV_BROWN`)** |
| **`GAME_12345`** | `GM12345` | `QK_KB_2` (0x7E42) | **`"12345"` 순환 틱(25ms당 1키) 무지연 연타** (토글) | 🩵 **하늘색 (`HSV_CYAN`)** |
| **`GAME_45`** | `GM45` | `QK_KB_3` (0x7E43) | **`"45"` 순환 틱(25ms당 1키) 무지연 연타** (토글) | 🔴 **빨간색 (`HSV_RED`)** |
| **`GAME_L_MOUSE`** | `GMLMS` | `QK_KB_4` (0x7E44) | **마우스 좌클릭 50ms 간격 무지연 연타** (토글) | 🩷 **자홍색 (`HSV_MAGENTA`)** |

### 💡 핵심 설계: Round-Robin State Machine & 논블로킹 메커니즘
1. **OS 입력 큐 과부하(Queue Lag) 방지**:
   - 일괄 동시 전송 대신 25ms 틱마다 배열 인덱스를 순환하며 단 1개 키씩 탭(`register` $\rightarrow$ `unregister`)하여 초당 40타 수준으로 부드럽게 분산 전송.
2. **토글 즉시 정지**:
   - 토글 OFF 이벤트 수신 시 즉시 모든 키에 대해 `unregister_code16()` 호출 및 인덱스 초기화로 **0.001초 이내 즉각 종료**.

---

## 3. 📂 디렉토리 구조

```
silakka54_keymap/
├── GEMINI.md            # [본 문서] 프로젝트 컨텍스트 및 AI 작업 가이드
├── WORK_LOG.md          # 상세 작업 일지 및 변경 이력
├── README.md            # 기본 저장소 설명서
├── silakka54.vil        # Vial GUI 레이아웃 백업 파일
├── keymaps/vial/        # 프로젝트 루트 펌웨어 소스
│   ├── config.h         # RGB 레이어 수 및 스플릿 설정
│   ├── keymap.c         # 키맵 및 커스텀 로직 (논블로킹 상태머신)
│   ├── rules.mk         # 마우스/RGB 기능 활성화
│   └── vial.json        # Vial GUI 커스텀 키코드 정의
├── scripts/
│   ├── build_firmware.sh # 펌웨어 원클릭 빌드 스크립트
│   └── setup_compiler.sh # 컴파일러 설치 안내
├── firmware/            # 컴파일 완료된 .uf2 바이너리
│   ├── silakka54_vial_20260820.uf2 # [최신] 순환 틱 상태머신 최적화 바이너리
│   └── silakka54_vial.uf2          # [심볼릭/최신] 기본 플래싱 대상
└── vial-qmk/            # QMK/Vial 빌드 트리 (실제 빌드 수행 경로)
```

---

## 4. 🛠️ 빌드 및 플래싱 방법

### 1) 빌드 도구 (Toolchain)
- ARM 컴파일러 경로: `~/.local/opt/arm-toolchain/bin` (Arm GNU Toolchain 10.3)
- 빌드 스크립트가 해당 경로를 자동으로 `PATH`에 등록하여 컴파일을 수행합니다.

### 2) 빌드 명령
```bash
bash scripts/build_firmware.sh
```
- 성공 시 `firmware/` 폴더에 타임스탬프 및 최신 `.uf2` 파일이 자동 생성/복사됩니다.

### 3) 실물 키보드 플래싱
1. 키보드의 **BOOT 버튼**을 누른 상태로 USB를 PC에 연결합니다.
2. `RPI-RP2` 볼륨이 마운트되면 **`firmware/silakka54_vial.uf2`** 파일을 드래그 앤 드롭으로 복사합니다.

---

## 5. 🌐 원격 저장소 동기화

- GitHub 원격 저장소: `https://github.com/kimjiho680629/Keyboard.git` (main 브랜치)
- 푸시 명령:
  ```bash
  git push origin main
  ```

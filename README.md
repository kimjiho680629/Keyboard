# Silakka54 Custom Keymap & Firmware Workspace

이 디렉토리는 **Silakka54 (54-key RP2040 Split Keyboard)** 키보드의 커스텀 키맵 백업, Vial 레이아웃 관리 및 QMK 컴파일 빌드 환경입니다.

## 📂 디렉토리 구조
```
silakka54_keymap/
├── WORK_LOG.md          # 지금까지의 작업 기록 및 펌웨어 기술 명세서
├── silakka54.vil        # Vial GUI 레이아웃 백업 파일
├── old/                 # 이전 원본 소스 및 빌드된 .uf2 펌웨어 백업
├── layouts/          # Vial GUI에서 백업/내보낸 (.vil / .json) 레이아웃 파일 저장소
├── firmware/         # 빌드된 최신 .uf2 바이너리 및 공식 릴리즈 백업
└── scripts/          # 빌드 및 컴파일러 툴체인 자동화 스크립트
    ├── setup_compiler.sh   # Arch Linux arm-none-eabi-gcc 툴체인 자동 설치
    └── build_firmware.sh   # Vial-QMK 소스 클론 및 RP2040 .uf2 펌웨어 컴파일
```

## 🚀 사용 가이드

### 1. GUI 방식 (Vial GUI / 웹)
* 브라우저에서 [https://vial.rocks](https://vial.rocks) 접속 또는 Vial GUI 실행
* 키맵 변경 후 `File` -> `Save layout`을 통해 `./layouts/` 폴더에 `.vil` 확장자로 백업 저장합니다.

### 2. C 소스 직접 컴파일 방식 (QMK / Vial-QMK)
1. **컴파일러 툴체인 설치 (Arch Linux):**
   ```bash
   ./scripts/setup_compiler.sh
   ```
2. **펌웨어 직접 컴파일 (`.uf2` 생성):**
   ```bash
   ./scripts/build_firmware.sh
   ```
3. 컴파일 결과물은 `./firmware/silakka54_vial_YYYYMMDD_HHMMSS.uf2` 형태로 자동 보관됩니다.

### ⚡ 키보드 플래싱 방법 (Bootloader 모드)
1. 키보드의 각 좌/우측 분할 보드의 **BOOT 버튼**을 누른 상태에서 USB 케이블을 PC에 연결합니다.
2. PC에 `RPI-RP2`라는 USB 드라이브가 인식됩니다.
3. 생성된 `.uf2` 파일을 `RPI-RP2` 드라이브로 드래그 앤 드롭(복사)하면 플래싱이 완료되고 자동으로 재부팅됩니다.

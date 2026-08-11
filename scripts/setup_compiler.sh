#!/usr/bin/env bash
set -e

echo "[+] Arch Linux 용 QMK / Vial-QMK arm-none-eabi 툴체인 설치 스크립트"
echo "[+] 아래 패키지를 설치합니다: arm-none-eabi-gcc, arm-none-eabi-newlib, qmk, git, cmake"

sudo pacman -S --needed --noconfirm arm-none-eabi-gcc arm-none-eabi-newlib qmk git cmake

echo "[+] 툴체인 설치가 완료되었습니다."
echo "[+] 'qmk setup' 명령을 실행하여 QMK 개발 환경을 초기화할 수 있습니다."

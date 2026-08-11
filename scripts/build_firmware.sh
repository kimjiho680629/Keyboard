#!/usr/bin/env bash
set -e

BUILD_DIR="$(cd "$(dirname "$0")/.." && pwd)"
QMK_DIR="$BUILD_DIR/vial-qmk"

echo "=== Silakka54 Firmware Build Script ==="

if [ ! -d "$QMK_DIR" ]; then
    echo "[!] vial-qmk 레포지토리가 존재하지 않습니다. 클론을 진행합니다..."
    git clone --recursive https://github.com/vial-kb/vial-qmk.git "$QMK_DIR"
fi

cd "$QMK_DIR"

echo "[+] silakka54 키보드 키맵 컴파일 시작..."
make silakka54:vial

if [ -f "silakka54_vial.uf2" ]; then
    cp "silakka54_vial.uf2" "$BUILD_DIR/firmware/silakka54_vial_$(date +%Y%m%d_%H%M%S).uf2"
    echo "[+] 성공: $BUILD_DIR/firmware/ 에 바이너리가 저장되었습니다."
fi

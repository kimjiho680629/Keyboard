# [핵심] Vial을 쓰려면 VIA도 무조건 켜야 합니다 (링커 에러 해결)
VIA_ENABLE = yes
VIAL_ENABLE = yes

# LED 및 하드웨어 설정
RGBLIGHT_ENABLE = yes
WS2812_DRIVER = vendor

# 링커 에러 방지를 위해 LTO는 끕니다
LTO_ENABLE = no

# 안 쓰는 기능 끄기 (충돌 방지)
COMBO_ENABLE = yes
TAP_DANCE_ENABLE = yes
KEY_OVERRIDE_ENABLE = no


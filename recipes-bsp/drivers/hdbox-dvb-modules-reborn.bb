SRCDATE = "20180820"

PROVIDES = "virtual/blindscan-dvbc virtual/blindscan-dvbs"

require hdbox-dvb-himodules.inc

SRC_URI[md5sum] = "996a54fa6a5c0c1080a6b02a89a3a24f"
SRC_URI[sha256sum] = "c7ded55a03054ee7b6c9ec239887301c674d41e3da96a4f68255a591b24490b0"

COMPATIBLE_MACHINE = "^(reborn)$"

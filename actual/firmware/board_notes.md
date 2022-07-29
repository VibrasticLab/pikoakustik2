# Catatan Desain

## Rekomendasi Revisi PCB P3
- STM32 tanpa resistor pull-up pada jalur SWD-IO
- STM32 USB-CDC pindah resistor pull-up dari jalur DM ke jalur DP
- ESP32 header programming cukup RX0, TX0, dan GND
- Cari pengganti Slot MMC yang serupa dan kompatibel
- Ada header terhubung ke 
    + ESP32 TX1 -- STM32 RX1
    + ESP32 RX1 -- STM32 TX1
    + ESP32 GND -- STM32 GND
- Smaller Push-Button:
    + STM32 Reset
    + ESP32 Flash
    + ESP32 Reset
- Charging process status/indicator/detection

## Komponen yang kurang di unit P3

### 01
- Bent White House Header untuk Battery

### 02
- LCD OLED
- Bent White House Header untuk Battery

### 03
- LCD OLED
- Bent White House Header untuk Battery

### 04
- LCD OLED
- Bent White House Header untuk Battery
- Modul Mic INMP441
- Power SW SPDT
- Check kompatibilitas ESP32-D

### 05
- LCD OLED
- Bent White House Header untuk Battery
- Modul Mic INMP441
- Power SW SPDT
- ESP-32 Chip
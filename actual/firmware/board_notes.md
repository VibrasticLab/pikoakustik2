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
    + STM32 Reset (Not actually need)
    + ESP32 Flash
    + ESP32 Reset (pake dipswitch?)
- Charging process status/indicator/detection
- ESP32 IO-12 must be low during boot
- ESP32 IO-05 must be low during boot
- ESP32 IO-02 should be pulled to GND when boot (no need for LED)
- ESP32 IO-15 can be low to prevent boot message (pake dipswitch?)

## Komponen yang kurang di unit P3

### 01
- Bent White House Header untuk Battery

### 02XX0H32XX0H32
- LCD OLED
- Bent White House Header untuk Battery

### 03
- LCD OLED
- Bent White House Header untuk Battery
- VDD STM32 di 4v

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

## Casing
- Tombol A gak 100% aligned
- Akrilik LED masih timbul
- Celah USB Port masih bercelah
- Mic Hole disesuaikan

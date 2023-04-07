# Catatan Desain

## Rekomendasi Revisi PCB P3
- STM32 tanpa resistor pull-up pada jalur SWD-IO
- STM32 USB-CDC pindah resistor pull-up dari jalur DM ke jalur DP
- ESP32 header programming cukup RX0, TX0, dan GND
- Cari pengganti Slot MMC yang serupa dan kompatibel
- STM32 USB-CDC ditambahkan ESD Protection
- STM32 RX (PA10) tidak boleh ada resistor pull-up
- STM32-ESP32 RX-TX pakai resistor 0 ohm
- STM32 MMC NSS tidak perlu ada resistor pull-up
- STM32 BOOT-0 dan BOOT-1 pake resistor pull-down
- STM32 tidak pakai (DNP) debouncing capacitor di tombol-tombol
- STM32 tambah header untuk UART
- Ada header terhubung ke
    + ESP32 TX1 -- STM32 RX1
    + ESP32 RX1 -- STM32 TX1
    + ESP32 GND -- STM32 GND
- Smaller Push-Button:
    + STM32 Reset
    + ESP32 Flash
    + ESP32 Reset
- Charging process status/indicator/detection
- Change STATUS_IO_0 to MISC
- Remove STATUS_IO_1 and STATUS_IO_2 lines
- ESP32 IO-12 should be low during boot via 0 ohm
- ESP32 IO-15 can be low to prevent boot message (pake dipswitch?)
- Gating dan Status terkait charge Battery (?)
	+ Gating jika battery kurang dari 50%
	+ Status jika battery sedang dicharge

## Komponen yang kurang di unit P3

### 01
- Bent White House Header untuk Battery

### 02
- Kiriman Xirca bulan Agustus
- Bent White House Header untuk Battery
- Broken STM32 chip
- Charging LED off

### 03
- Bent White House Header untuk Battery
- VDD STM32 di 4v
- STM32 RX robek

### 04
- Bent White House Header untuk Battery
- Modul Mic INMP441
- Power SW SPDT
- Check kompatibilitas ESP32-D

### 05
- Bent White House Header untuk Battery
- Modul Mic INMP441
- Power SW SPDT
- ESP-32 Chip

## Casing
- Tombol A gak 100% aligned
- Akrilik LED masih timbul
- Celah USB Port masih bercelah
- Mic Hole disesuaikan

# Compatible STM32

## Minimum Requirement
- arsitektur ARM Cortex-M4
- paket chip LQFP64
- PLL Clock minimal 72MHz
- SRAM minimal 48kB
- Flash minimal 250kB
- tersedia SPI2 I2S dengan clock 48MHz
- tersedia SPI3 untuk SDCard MMC
- tersedia UART1 untuk tukar data dengan ESP32
- tersedia USB sebagai serial-CDC untuk testing
    + Sebagai alternatif dapat digunakan UART2

## Part Pattern
- Antara STM32F3 atau STM32F4
- Paket chip biasanya (dimana x bernilai 3 atau 4):
    + STM32FxyyRB (cek Flash dan SRAM)
    + STM32FxyyRC
    + STM32FxyyRD
    + STM32FxyyRE
    
**Catatan:** untuk cek Flash dan SRAM, dapat dilakukan dengan kompilasi program untuk target chip, kemudian memperhatikan linker mengalokasikan alamat di binary akhir dan terlihat apakah cukup atau tidak dengan yang tersedia.

## Yang saat ini telah dipakai/tersedia

### F401RE
- [x] ARM Cortex-M4
- [x] LQFP64
- [x] PLL Clock >= 72MHz
- [x] SRAM >= 48kB (96kB)
- [x] Flash >= 250 kB (512kB)
- [x] SPI2 I2S =48MHz
- [x] SPI3 SDCard
- [x] UART1
- [x] USB-CDC
    + [x] UART2

### F303RC
- [x] ARM Cortex-M4
- [x] LQFP64
- [x] PLL Clock >= 72MHz
- [x] SRAM >= 48kB
- [x] Flash >= 250 kB
- [x] SPI2 I2S =48MHz
- [x] SPI3 SDCard
- [x] UART1
- [x] USB-CDC
    + [x] UART2

## Alternative Checking

### F334R8
- [x] ARM Cortex-M4
- [x] LQFP64
- [x] PLL Clock >= 72MHz
- [ ] SRAM >= 48kB (16kB)
- [ ] Flash >= 250 kB (64kB)
- [ ] SPI2 I2S =48MHz (No SPI2)
- [ ] SPI3 SDCard (No SPI3)
- [x] UART1
- [ ] USB-CDC
    - [x] UART2 

**Keputusan:** Tidak Bisa karena fitur minimum tidak terpenuhi

### F302C8

- [x] ARM Cortex-M4
- [ ] LQFP64 (LQF48)
- [x] PLL Clock >= 72MHz
- [ ] SRAM >= 48kB (16kB)
- [ ] Flash >= 250 kB (64kB)
- [x] SPI2 I2S =48MHz
- [x] SPI3 SDCard
- [x] UART1
- [x] USB-CDC
    - [x] UART2

**Keputusan:** Perlu redesign PCB dan recheck lebih jauh mengingat bukan LQFP64

### F301C8

- [x] ARM Cortex-M4
- [ ] LQFP64 (LQF48)
- [x] PLL Clock >= 72MHz
- [ ] SRAM >= 48kB (16kB)
- [ ] Flash >= 250 kB (64kB)
- [x] SPI2 I2S =48MHz
- [x] SPI3 SDCard
- [ ] USB-CDC
    - [x] UART2

**Keputusan:** Perlu redesign PCB dan recheck lebih jauh mengingat bukan LQFP64

### F303RB

- [x] ARM Cortex-M4
- [x] LQFP64
- [x] PLL Clock >= 72MHz
- [ ] SRAM >= 48kB (40kB)
- [ ] Flash >= 250 kB (128kB)
- [x] SPI2 I2S =48MHz
- [x] SPI3 SDCard
- [x] UART1
- [x] USB-CDC
    - [x] UART2

**Keputusan:** PCB kompatibel namun perlu re-testing mengingat ukuran Flash dan SRAM lebih kecil


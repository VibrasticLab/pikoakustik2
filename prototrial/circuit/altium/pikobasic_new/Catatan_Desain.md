Berikut Penjelasan terkait pilihan desain yang ada di **listkoreksi.txt**

---

**Q: apa tujuan penambahan R 1Mega Ohm di pin SD_mode MAX98357AETE ?**

**A:**

Tujuannya adalah untuk resistor pull-up yang dapat digunakan kontrol chip mana yang di-shutdown
(karena chip MAX98357A untuk channel L dan R nyala bergantian).

sedangkan untuk nilainya, menurut datasheet MAX98357A yang tersedia di situs [Maxim](https://datasheets.maximintegrated.com/en/ds/MAX98357A-MAX98357B.pdf), sesuai tabel 5 dan tabel 6 di halaman 17,
nilai output mono I2S yang digunakan adalah word (L+R)/2, dimana nilai minimum 634k&#937; namun Adafruit mencontohkan 1M&#937; seperti yang ada [disini](https://www.adafruit.com/product/3006)

---

**Q:apa tujuan penambahan R 10K Ohm di pin IO15 _ PIN 23 ESP-WROOM32 ?**

**A:**

Tujuannya untuk disable boot message pada UART0 (selain recompile bootloader), sesuai diskusi di [forum ini](https://www.esp32.com/viewtopic.php?t=1658)

STM32 dan ESP32 bertukar data (untuk status proses diganti pakai I/O) via UART0, maka UART shell diharapkan bersih dari:
- debug message (termasuk startup message)
- input echo
- error response

Sejauh ini source code untuk STM2F401RE dan ESP32 sudah mampu menggunakan UART yang bersih, hanya proper request dan proper response yang dikerjakan oleh kedua chip.

---

**Q: klo skr uart dari stm32 dan ESP32 semua digabung via UART0, kemungkinan akan bermasalah kedepannya,**

**A:**

Sebelum lebih jauh membahas, berikut penjelasan singkat pilihan desain program

**ESP32**

Untuk ESP32, program ditulis menggunakan ESP-IDF dengan FreeRTOS untuk scheduling, sehingga:
- Draw LCD, Interrupt I/O, UART-Shell, seterusnya, bisa running di thread-thead terpisah dan tidak harus synchron satu sama lain
- Telah diuji menggunakan UART-0 dan UART-2 untuk menggunakan shell bersamaan, ESP32 selalu crash dan reboot. Kemungkinan karena:
    + SRAM ESP32 tidak cukup untuk dua UART Shell
    + Pin UART2 di map ke pin yang tidak selayaknya di map untuk UART2

Problem pada multi-UART juga muncul di platform Arduino seperti pada [issue ini](https://github.com/espressif/arduino-esp32/issues/1314).

**Kesimpulan ESP32:** Butuh re-check lagi apakah terkait sebab ESP32 crash saat dua UART Shell digunakan bersamaan. Saat ini hanya bisa UART0

**STM32**

Untuk STM32, program ditulis menggunakan ChibiOS/RT untuk scheduling dan driver, sehingga:
- Rutin Audiometri, Interrupt I/O, Tone Generation UART-Shell, seterusnya, bisa running di thread atau DMA terpisah dan tidak harus synchron satu sama lain
- STM32 saat sudah menggunakan 2 UART Shell:
    + UART1 ke ESP32
    + UART USB-CDC untuk debugging via micro USB
- Chip STM32 yang digunakan selanjutnya adalah seri F303RC, dimana SRAM nya separuh F401RE yang saat ini digunakan

**Kesimpulan STM32:** Butuh re-check lagi apakah STM32F303RC cukup untuk ditambah satu UART Shell lagi, baik ukuran SRAM maupun ketersediaan pinout

**Problem Utama:**

menurut saya untuk sekarang problem utama adalah UART0 digunakan oleh ESP32 sebagai programmer, sehingga saat programming ESP32,
maka chip STM32 harus ditahan reset agar UART STM32 tidak merespon UART programming dan tidak mengganggu jalannya flashing ESP32

---

**Q: warna LED tolong ditentukan untuk masing2 nya.**

**A:**

Segera

---

**Q: footprint dan 3D STEP yg belum ada.**

**A:**

Sedang dikerjakan dan mencari di internet

---

**Q: designator komponent tidak ada.**

Designator yang pakai biasanya mengikuti area di sekitar chip atau grup fungsi.

Semisal resistor sekitar ESP32, semua designator mengikuti pola R-ESP-, C-ESP, dimana menandakan komponen tersebut di sekitar chip ESP32 (mempermudah saya yang nyolder sendirian untuk mencari area di PCB nya)

  Tapi jika designator dengan anotasi angka saja adalah standar, maka saya segera perbaiki nama-nama designator mengikuti standar tersebut

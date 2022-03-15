EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr User 9843 7874
encoding utf-8
Sheet 2 4
Title "ESP32 OLED User Interface"
Date "2022-02-14"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:GND #PWR03
U 1 1 620A2D54
P 2200 5200
F 0 "#PWR03" H 2200 4950 50  0001 C CNN
F 1 "GND" H 2205 5027 50  0000 C CNN
F 2 "" H 2200 5200 50  0001 C CNN
F 3 "" H 2200 5200 50  0001 C CNN
	1    2200 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 5050 2200 5150
Text HLabel 2350 5150 2    50   UnSpc ~ 0
ESP32_GND
Wire Wire Line
	2350 5150 2200 5150
Connection ~ 2200 5150
Wire Wire Line
	2200 5150 2200 5200
Wire Wire Line
	2800 3250 3050 3250
Wire Wire Line
	2800 3350 3050 3350
Text Label 3050 3250 0    50   ~ 0
MIC_SCK
Text Label 3050 3350 0    50   ~ 0
MIC_WS
Wire Wire Line
	2800 3850 3050 3850
Text Label 3050 3850 0    50   ~ 0
OLED_SDA
Wire Wire Line
	2800 3950 3050 3950
Text Label 3050 3950 0    50   ~ 0
OLED_SCL
$Comp
L SSD1306-128x64_OLED:SSD1306 Brd1
U 1 1 620D05FD
P 4800 3450
F 0 "Brd1" V 4385 3508 50  0000 C CNN
F 1 "SSD1306" V 4476 3508 50  0000 C CNN
F 2 "" H 4800 3700 50  0001 C CNN
F 3 "" H 4800 3700 50  0001 C CNN
	1    4800 3450
	0    1    1    0   
$EndComp
$Comp
L power:VDD #PWR09
U 1 1 620D1F7D
P 5450 3200
F 0 "#PWR09" H 5450 3050 50  0001 C CNN
F 1 "VDD" H 5465 3373 50  0001 C CNN
F 2 "" H 5450 3200 50  0001 C CNN
F 3 "" H 5450 3200 50  0001 C CNN
	1    5450 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 620D25FA
P 5650 3300
F 0 "#PWR010" H 5650 3050 50  0001 C CNN
F 1 "GND" H 5655 3127 50  0001 C CNN
F 2 "" H 5650 3300 50  0001 C CNN
F 3 "" H 5650 3300 50  0001 C CNN
	1    5650 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 3400 5450 3400
Wire Wire Line
	5650 3300 5150 3300
Text Label 6050 3500 0    50   ~ 0
OLED_SCL
Text Label 6050 3600 0    50   ~ 0
OLED_SDA
$Comp
L Connector:Conn_01x06_Male J-PROG1
U 1 1 620D757C
P 4700 4700
F 0 "J-PROG1" H 4808 5081 50  0000 C CNN
F 1 "Conn_01x06_Male" H 4808 4990 50  0000 C CNN
F 2 "" H 4700 4700 50  0001 C CNN
F 3 "~" H 4700 4700 50  0001 C CNN
	1    4700 4700
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR08
U 1 1 620DD32C
P 5200 4500
F 0 "#PWR08" H 5200 4350 50  0001 C CNN
F 1 "VDD" H 5215 4673 50  0000 C CNN
F 2 "" H 5200 4500 50  0001 C CNN
F 3 "" H 5200 4500 50  0001 C CNN
	1    5200 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 4500 5200 4500
Wire Wire Line
	4900 4600 5150 4600
Text Label 5150 4600 0    50   ~ 0
RX0
Wire Wire Line
	4900 4700 5150 4700
Text Label 5150 4700 0    50   ~ 0
TX0
Wire Wire Line
	4900 4800 5150 4800
Text Label 5150 4800 0    50   ~ 0
ESP_NRST
Wire Wire Line
	4900 4900 5150 4900
Text Label 5150 4900 0    50   ~ 0
ESP_FLASH
$Comp
L power:GND #PWR07
U 1 1 620E05E4
P 5150 5000
F 0 "#PWR07" H 5150 4750 50  0001 C CNN
F 1 "GND" H 5155 4827 50  0000 C CNN
F 2 "" H 5150 5000 50  0001 C CNN
F 3 "" H 5150 5000 50  0001 C CNN
	1    5150 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 5000 5150 5000
$Comp
L Device:R R-BTN1
U 1 1 620E5340
P 6800 2400
F 0 "R-BTN1" H 6870 2446 50  0001 L CNN
F 1 "10K" H 6870 2355 50  0000 L CNN
F 2 "" V 6730 2400 50  0001 C CNN
F 3 "~" H 6800 2400 50  0001 C CNN
	1    6800 2400
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW-BTN1
U 1 1 620E5C80
P 6800 2850
F 0 "SW-BTN1" V 6754 2998 50  0000 L CNN
F 1 "SW_Push" V 6845 2998 50  0000 L CNN
F 2 "" H 6800 3050 50  0001 C CNN
F 3 "~" H 6800 3050 50  0001 C CNN
	1    6800 2850
	0    1    1    0   
$EndComp
$Comp
L power:VDD #PWR012
U 1 1 620E6422
P 6800 2150
F 0 "#PWR012" H 6800 2000 50  0001 C CNN
F 1 "VDD" H 6815 2323 50  0000 C CNN
F 2 "" H 6800 2150 50  0001 C CNN
F 3 "" H 6800 2150 50  0001 C CNN
	1    6800 2150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR013
U 1 1 620E87F4
P 6800 3150
F 0 "#PWR013" H 6800 2900 50  0001 C CNN
F 1 "GND" H 6805 2977 50  0000 C CNN
F 2 "" H 6800 3150 50  0001 C CNN
F 3 "" H 6800 3150 50  0001 C CNN
	1    6800 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 2550 6800 2600
Wire Wire Line
	6800 3050 6800 3150
Wire Wire Line
	6800 2600 6900 2600
Connection ~ 6800 2600
Wire Wire Line
	6800 2600 6800 2650
Wire Wire Line
	6800 2150 6800 2250
$Comp
L Device:R R-BTN2
U 1 1 620EBEE3
P 6850 4200
F 0 "R-BTN2" H 6920 4246 50  0001 L CNN
F 1 "10K" H 6920 4155 50  0000 L CNN
F 2 "" V 6780 4200 50  0001 C CNN
F 3 "~" H 6850 4200 50  0001 C CNN
	1    6850 4200
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW-BTN2
U 1 1 620EBFF3
P 6850 4650
F 0 "SW-BTN2" V 6804 4798 50  0000 L CNN
F 1 "SW_Push" V 6895 4798 50  0000 L CNN
F 2 "" H 6850 4850 50  0001 C CNN
F 3 "~" H 6850 4850 50  0001 C CNN
	1    6850 4650
	0    1    1    0   
$EndComp
$Comp
L power:VDD #PWR014
U 1 1 620EBFFD
P 6850 3950
F 0 "#PWR014" H 6850 3800 50  0001 C CNN
F 1 "VDD" H 6865 4123 50  0000 C CNN
F 2 "" H 6850 3950 50  0001 C CNN
F 3 "" H 6850 3950 50  0001 C CNN
	1    6850 3950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 620EC007
P 6850 4950
F 0 "#PWR015" H 6850 4700 50  0001 C CNN
F 1 "GND" H 6855 4777 50  0000 C CNN
F 2 "" H 6850 4950 50  0001 C CNN
F 3 "" H 6850 4950 50  0001 C CNN
	1    6850 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 4350 6850 4400
Wire Wire Line
	6850 4850 6850 4950
Wire Wire Line
	6850 4400 6950 4400
Connection ~ 6850 4400
Wire Wire Line
	6850 4400 6850 4450
Wire Wire Line
	6850 3950 6850 4050
Text Label 6900 2600 0    50   ~ 0
BTN_ACT_A
Text Label 8000 3450 0    50   ~ 0
BTN_PAGE
Text Label 6950 4400 0    50   ~ 0
BTN_ACT_B
Wire Wire Line
	7900 3000 7900 3100
Wire Wire Line
	7900 3450 7900 3500
Connection ~ 7900 3450
Wire Wire Line
	7900 3450 8000 3450
Wire Wire Line
	7900 3900 7900 4000
Wire Wire Line
	7900 3400 7900 3450
$Comp
L power:GND #PWR017
U 1 1 620F2982
P 7900 4000
F 0 "#PWR017" H 7900 3750 50  0001 C CNN
F 1 "GND" H 7905 3827 50  0000 C CNN
F 2 "" H 7900 4000 50  0001 C CNN
F 3 "" H 7900 4000 50  0001 C CNN
	1    7900 4000
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR016
U 1 1 620F2978
P 7900 3000
F 0 "#PWR016" H 7900 2850 50  0001 C CNN
F 1 "VDD" H 7915 3173 50  0000 C CNN
F 2 "" H 7900 3000 50  0001 C CNN
F 3 "" H 7900 3000 50  0001 C CNN
	1    7900 3000
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW-BTN3
U 1 1 620F296E
P 7900 3700
F 0 "SW-BTN3" V 7854 3848 50  0000 L CNN
F 1 "SW_Push" V 7945 3848 50  0000 L CNN
F 2 "" H 7900 3900 50  0001 C CNN
F 3 "~" H 7900 3900 50  0001 C CNN
	1    7900 3700
	0    1    1    0   
$EndComp
$Comp
L Device:R R-BTN3
U 1 1 620F281C
P 7900 3250
F 0 "R-BTN3" H 7970 3296 50  0001 L CNN
F 1 "10K" H 7970 3205 50  0000 L CNN
F 2 "" V 7830 3250 50  0001 C CNN
F 3 "~" H 7900 3250 50  0001 C CNN
	1    7900 3250
	1    0    0    -1  
$EndComp
$Comp
L INMP441:INMP441 U2
U 1 1 6212299A
P 4850 1750
F 0 "U2" H 4825 1825 50  0000 C CNN
F 1 "INMP441" H 4825 1734 50  0000 C CNN
F 2 "" H 4850 1750 50  0001 C CNN
F 3 "" H 4850 1750 50  0001 C CNN
	1    4850 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 2000 5350 2000
Text Label 5350 2000 0    50   ~ 0
MIC_WS
Wire Wire Line
	5200 2100 5350 2100
Text Label 5350 2100 0    50   ~ 0
MIC_SCK
$Comp
L power:GND #PWR011
U 1 1 6216CD4D
P 5800 2150
F 0 "#PWR011" H 5800 1900 50  0001 C CNN
F 1 "GND" H 5805 1977 50  0000 C CNN
F 2 "" H 5800 2150 50  0001 C CNN
F 3 "" H 5800 2150 50  0001 C CNN
	1    5800 2150
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR05
U 1 1 62161E6A
P 4000 1900
F 0 "#PWR05" H 4000 1750 50  0001 C CNN
F 1 "VDD" H 4015 2073 50  0000 C CNN
F 2 "" H 4000 1900 50  0001 C CNN
F 3 "" H 4000 1900 50  0001 C CNN
	1    4000 1900
	1    0    0    -1  
$EndComp
Text Label 4200 2100 0    50   ~ 0
MIC_DATA
Wire Wire Line
	4450 2100 4200 2100
Wire Wire Line
	4450 2000 4000 2000
Wire Wire Line
	4450 1900 4000 1900
$Comp
L power:GND #PWR06
U 1 1 6216178F
P 4000 2000
F 0 "#PWR06" H 4000 1750 50  0001 C CNN
F 1 "GND" H 4005 1827 50  0000 C CNN
F 2 "" H 4000 2000 50  0001 C CNN
F 3 "" H 4000 2000 50  0001 C CNN
	1    4000 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 2450 1550 2450
Text Label 1300 2450 2    50   ~ 0
ESP_NRST
Connection ~ 1550 2450
Wire Wire Line
	1550 2450 1550 2400
Wire Wire Line
	1600 2450 1550 2450
Wire Wire Line
	1550 2000 1550 2100
$Comp
L power:VDD #PWR01
U 1 1 620B9A10
P 1550 2000
F 0 "#PWR01" H 1550 1850 50  0001 C CNN
F 1 "VDD" H 1565 2173 50  0000 C CNN
F 2 "" H 1550 2000 50  0001 C CNN
F 3 "" H 1550 2000 50  0001 C CNN
	1    1550 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R-ESP1
U 1 1 620B7E35
P 1550 2250
F 0 "R-ESP1" H 1620 2296 50  0001 L CNN
F 1 "10K" H 1620 2205 50  0000 L CNN
F 2 "" V 1480 2250 50  0001 C CNN
F 3 "~" H 1550 2250 50  0001 C CNN
	1    1550 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 2050 2900 2150
$Comp
L power:VDD #PWR04
U 1 1 620B742A
P 2900 2050
F 0 "#PWR04" H 2900 1900 50  0001 C CNN
F 1 "VDD" H 2915 2223 50  0000 C CNN
F 2 "" H 2900 2050 50  0001 C CNN
F 3 "" H 2900 2050 50  0001 C CNN
	1    2900 2050
	1    0    0    -1  
$EndComp
Text Label 3300 2450 0    50   ~ 0
ESP_FLASH
Connection ~ 2900 2450
Wire Wire Line
	2800 2450 2900 2450
$Comp
L Device:R R-ESP2
U 1 1 620B4635
P 2900 2300
F 0 "R-ESP2" H 2970 2346 50  0001 L CNN
F 1 "10K" H 2970 2255 50  0000 L CNN
F 2 "" V 2830 2300 50  0001 C CNN
F 3 "~" H 2900 2300 50  0001 C CNN
	1    2900 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 2000 2200 2250
Connection ~ 2200 2000
Wire Wire Line
	2350 2000 2200 2000
Text HLabel 2350 2000 2    50   UnSpc ~ 0
ESP32_VDD
Text HLabel 8250 1650 2    50   Input ~ 0
ESP32_RX
Text HLabel 8250 1450 2    50   Output ~ 0
ESP32_TX
$Comp
L Device:R R-UART2
U 1 1 620A5BC5
P 8000 1650
F 0 "R-UART2" V 7793 1650 50  0001 C CNN
F 1 "0" V 7884 1650 50  0000 C CNN
F 2 "" V 7930 1650 50  0001 C CNN
F 3 "~" H 8000 1650 50  0001 C CNN
	1    8000 1650
	0    1    1    0   
$EndComp
$Comp
L Device:R R-UART1
U 1 1 620A5150
P 8000 1450
F 0 "R-UART1" V 7793 1450 50  0001 C CNN
F 1 "0" V 7884 1450 50  0000 C CNN
F 2 "" V 7930 1450 50  0001 C CNN
F 3 "~" H 8000 1450 50  0001 C CNN
	1    8000 1450
	0    1    1    0   
$EndComp
Wire Wire Line
	2200 1900 2200 2000
$Comp
L power:VDD #PWR02
U 1 1 620A1FB3
P 2200 1900
F 0 "#PWR02" H 2200 1750 50  0001 C CNN
F 1 "VDD" H 2215 2073 50  0000 C CNN
F 2 "" H 2200 1900 50  0001 C CNN
F 3 "" H 2200 1900 50  0001 C CNN
	1    2200 1900
	1    0    0    -1  
$EndComp
$Comp
L RF_Module:ESP32-WROOM-32 U1
U 1 1 620A12A5
P 2200 3650
F 0 "U1" H 2200 5231 50  0000 C CNN
F 1 "ESP32-WROOM-32" H 2200 5140 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 2200 2150 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf" H 1900 3700 50  0001 C CNN
	1    2200 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 2450 3300 2450
Wire Wire Line
	5450 3400 5450 3200
Wire Wire Line
	5800 1900 5800 2150
Wire Wire Line
	5200 1900 5800 1900
Wire Wire Line
	8150 1450 8250 1450
Wire Wire Line
	8150 1650 8250 1650
Text Label 7700 1450 2    50   ~ 0
TX0
Wire Wire Line
	7700 1450 7850 1450
Text Label 7700 1650 2    50   ~ 0
RX0
Wire Wire Line
	7700 1650 7850 1650
Wire Wire Line
	2800 2550 3050 2550
Wire Wire Line
	2800 2750 3050 2750
Text Label 3050 2550 0    50   ~ 0
TX0
Text Label 3050 2750 0    50   ~ 0
RX0
Wire Wire Line
	2800 2650 3050 2650
Text Label 3050 2650 0    50   ~ 0
LED
$Comp
L power:VDD #PWR046
U 1 1 620B8AB8
P 3450 5500
F 0 "#PWR046" H 3450 5350 50  0001 C CNN
F 1 "VDD" H 3465 5673 50  0000 C CNN
F 2 "" H 3450 5500 50  0001 C CNN
F 3 "" H 3450 5500 50  0001 C CNN
	1    3450 5500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R-LED1
U 1 1 620B8F41
P 3450 5750
F 0 "R-LED1" H 3520 5796 50  0001 L CNN
F 1 "330" H 3520 5750 50  0000 L CNN
F 2 "" V 3380 5750 50  0001 C CNN
F 3 "~" H 3450 5750 50  0001 C CNN
	1    3450 5750
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 620B9B19
P 3450 6150
F 0 "D1" V 3489 6032 50  0001 R CNN
F 1 "LED" V 3398 6032 50  0001 R CNN
F 2 "" H 3450 6150 50  0001 C CNN
F 3 "~" H 3450 6150 50  0001 C CNN
	1    3450 6150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3450 6300 3450 6450
Text Label 3450 6450 0    50   ~ 0
LED
Wire Wire Line
	3450 5900 3450 6000
Wire Wire Line
	3450 5500 3450 5600
Text Label 3050 4050 0    50   ~ 0
MIC_DATA
Wire Wire Line
	2800 4050 3050 4050
Wire Wire Line
	5150 3500 5950 3500
$Comp
L Device:R R-OLED1
U 1 1 62169589
P 5850 3250
F 0 "R-OLED1" H 5920 3296 50  0001 L CNN
F 1 "10K" H 5650 3300 50  0000 L CNN
F 2 "" V 5780 3250 50  0001 C CNN
F 3 "~" H 5850 3250 50  0001 C CNN
	1    5850 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R-OLED2
U 1 1 6216A4C0
P 5950 3250
F 0 "R-OLED2" H 6020 3296 50  0001 L CNN
F 1 "10K" H 6000 3300 50  0000 L CNN
F 2 "" V 5880 3250 50  0001 C CNN
F 3 "~" H 5950 3250 50  0001 C CNN
	1    5950 3250
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR047
U 1 1 6216AE62
P 5900 3050
F 0 "#PWR047" H 5900 2900 50  0001 C CNN
F 1 "VDD" H 5915 3223 50  0000 C CNN
F 2 "" H 5900 3050 50  0001 C CNN
F 3 "" H 5900 3050 50  0001 C CNN
	1    5900 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 3100 5950 3050
Wire Wire Line
	5950 3050 5900 3050
Wire Wire Line
	5850 3100 5850 3050
Wire Wire Line
	5850 3050 5900 3050
Connection ~ 5900 3050
Wire Wire Line
	5950 3400 5950 3500
Connection ~ 5950 3500
Wire Wire Line
	5950 3500 6050 3500
Wire Wire Line
	5850 3400 5850 3600
Wire Wire Line
	5150 3600 5850 3600
Connection ~ 5850 3600
Wire Wire Line
	5850 3600 6050 3600
Wire Wire Line
	2800 4150 3050 4150
Text Label 3050 4150 0    50   ~ 0
BTN_ACT_A
Wire Wire Line
	2800 4250 3050 4250
Text Label 3050 4250 0    50   ~ 0
BTN_ACT_B
Wire Wire Line
	2800 4350 3050 4350
Text Label 3050 4350 0    50   ~ 0
BTN_PAGE
$EndSCHEMATC

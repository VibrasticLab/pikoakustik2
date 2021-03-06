EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_ST_STM32F4:STM32F401RETx U1
U 1 1 62079113
P 6000 3500
F 0 "U1" H 5950 5381 50  0000 C CNN
F 1 "STM32F401RETx" H 5950 5290 50  0000 C CNN
F 2 "Package_QFP:LQFP-64_10x10mm_P0.5mm" H 5400 1800 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00102166.pdf" H 6000 3500 50  0001 C CNN
	1    6000 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 1800 6200 1800
Wire Wire Line
	5800 1800 5900 1800
Wire Wire Line
	6000 1800 5900 1800
Connection ~ 5900 1800
Wire Wire Line
	6100 1800 6000 1800
Connection ~ 6100 1800
Connection ~ 6000 1800
Connection ~ 6200 1800
Wire Wire Line
	6200 1650 6200 1800
$Comp
L power:VDD #PWR01
U 1 1 6207B1C2
P 6200 1650
F 0 "#PWR01" H 6200 1500 50  0001 C CNN
F 1 "VDD" H 6215 1823 50  0000 C CNN
F 2 "" H 6200 1650 50  0001 C CNN
F 3 "" H 6200 1650 50  0001 C CNN
	1    6200 1650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R-RST1
U 1 1 6207EED1
P 5150 1800
F 0 "R-RST1" H 5220 1846 50  0000 L CNN
F 1 "10K" H 5220 1755 50  0000 L CNN
F 2 "" V 5080 1800 50  0001 C CNN
F 3 "~" H 5150 1800 50  0001 C CNN
	1    5150 1800
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR06
U 1 1 6207F72E
P 5150 1550
F 0 "#PWR06" H 5150 1400 50  0001 C CNN
F 1 "VDD" H 5165 1723 50  0000 C CNN
F 2 "" H 5150 1550 50  0001 C CNN
F 3 "" H 5150 1550 50  0001 C CNN
	1    5150 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 2000 5150 2000
Wire Wire Line
	5150 2000 5150 1950
Wire Wire Line
	5150 1550 5150 1650
$Comp
L power:GND #PWR05
U 1 1 6208B8CA
P 5000 2200
F 0 "#PWR05" H 5000 1950 50  0001 C CNN
F 1 "GND" H 5005 2027 50  0000 C CNN
F 2 "" H 5000 2200 50  0001 C CNN
F 3 "" H 5000 2200 50  0001 C CNN
	1    5000 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 2200 5000 2200
$Comp
L Device:C C-VCAP1
U 1 1 6208C33D
P 4750 2550
F 0 "C-VCAP1" H 4865 2596 50  0000 L CNN
F 1 "4.7uF" H 4865 2505 50  0000 L CNN
F 2 "" H 4788 2400 50  0001 C CNN
F 3 "~" H 4750 2550 50  0001 C CNN
	1    4750 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 6209167D
P 4750 2800
F 0 "#PWR03" H 4750 2550 50  0001 C CNN
F 1 "GND" H 4755 2627 50  0000 C CNN
F 2 "" H 4750 2800 50  0001 C CNN
F 3 "" H 4750 2800 50  0001 C CNN
	1    4750 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 2400 4750 2400
Wire Wire Line
	4750 2800 4750 2700
$Comp
L power:VDD #PWR04
U 1 1 62093119
P 4900 2000
F 0 "#PWR04" H 4900 1850 50  0001 C CNN
F 1 "VDD" H 4915 2173 50  0000 C CNN
F 2 "" H 4900 2000 50  0001 C CNN
F 3 "" H 4900 2000 50  0001 C CNN
	1    4900 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 2500 4900 2500
Wire Wire Line
	4900 2500 4900 2000
Wire Wire Line
	5300 3600 4900 3600
Wire Wire Line
	5300 3700 4900 3700
Wire Wire Line
	5300 3800 4900 3800
Text Label 4900 3600 0    50   ~ 0
BTN_A
Text Label 4900 3700 0    50   ~ 0
BTN_B
Text Label 4900 3800 0    50   ~ 0
BTN_C
Wire Wire Line
	5300 4600 4950 4600
Text Label 4950 4600 0    50   ~ 0
MMC_SCK
Wire Wire Line
	5300 4700 4950 4700
Text Label 4950 4700 0    50   ~ 0
MMC_MISO
Wire Wire Line
	5300 4800 4950 4800
Text Label 4950 4800 0    50   ~ 0
MMC_MOSI
$Comp
L OPL_Connector:MICRO-SD-CARD-SOCKET-9P_ST-TF-003A_ SD1
U 1 1 62099BF3
P 2500 1550
F 0 "SD1" H 3028 1642 45  0000 L CNN
F 1 "MICRO-SD-CARD-SOCKET-9P_ST-TF-003A_" H 3028 1558 45  0000 L CNN
F 2 "" H 2500 1550 50  0001 C CNN
F 3 "" H 2500 1550 50  0001 C CNN
F 4 "ST-TF-003A" H 2530 1700 20  0001 C CNN "MPN"
F 5 "320090000" H 2530 1700 20  0001 C CNN "SKU"
	1    2500 1550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R-MMC1
U 1 1 6209A601
P 1500 1150
F 0 "R-MMC1" V 1293 1150 50  0000 C CNN
F 1 "10K" V 1384 1150 50  0000 C CNN
F 2 "" V 1430 1150 50  0001 C CNN
F 3 "~" H 1500 1150 50  0001 C CNN
	1    1500 1150
	0    1    1    0   
$EndComp
$Comp
L Device:R R-MMC2
U 1 1 6209B507
P 1500 1750
F 0 "R-MMC2" V 1293 1750 50  0000 C CNN
F 1 "10K" V 1384 1750 50  0000 C CNN
F 2 "" V 1430 1750 50  0001 C CNN
F 3 "~" H 1500 1750 50  0001 C CNN
	1    1500 1750
	0    1    1    0   
$EndComp
$Comp
L Device:R R-MMC3
U 1 1 6209B81D
P 1500 1850
F 0 "R-MMC3" V 1293 1850 50  0000 C CNN
F 1 "10K" V 1384 1850 50  0000 C CNN
F 2 "" V 1430 1850 50  0001 C CNN
F 3 "~" H 1500 1850 50  0001 C CNN
	1    1500 1850
	0    1    1    0   
$EndComp
Wire Wire Line
	1800 1150 1650 1150
Wire Wire Line
	1800 1750 1650 1750
Wire Wire Line
	1800 1850 1650 1850
Wire Wire Line
	1350 1850 1300 1850
Wire Wire Line
	1300 1850 1300 1750
Wire Wire Line
	1300 1150 1350 1150
Wire Wire Line
	1350 1750 1300 1750
Connection ~ 1300 1750
Wire Wire Line
	1300 1750 1300 1450
$Comp
L power:VDD #PWR02
U 1 1 6209D752
P 1300 1100
F 0 "#PWR02" H 1300 950 50  0001 C CNN
F 1 "VDD" H 1315 1273 50  0000 C CNN
F 2 "" H 1300 1100 50  0001 C CNN
F 3 "" H 1300 1100 50  0001 C CNN
	1    1300 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 1100 1300 1150
Connection ~ 1300 1150
Wire Wire Line
	1800 1450 1300 1450
Connection ~ 1300 1450
Wire Wire Line
	1300 1450 1300 1150
Wire Wire Line
	1800 1250 1650 1250
Text Label 1650 1250 0    50   ~ 0
MMC_NSS
Wire Wire Line
	1800 1350 1650 1350
Text Label 1650 1350 0    50   ~ 0
MMC_MOSI
Wire Wire Line
	1800 1550 1650 1550
Text Label 1650 1550 0    50   ~ 0
MMC_SCK
$Comp
L power:GND #PWR07
U 1 1 620A2D70
P 1150 1650
F 0 "#PWR07" H 1150 1400 50  0001 C CNN
F 1 "GND" H 1155 1477 50  0000 C CNN
F 2 "" H 1150 1650 50  0001 C CNN
F 3 "" H 1150 1650 50  0001 C CNN
	1    1150 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 1650 1150 1650
Text Label 1700 1750 0    50   ~ 0
MMC_MISO
$Comp
L power:GND #PWR014
U 1 1 620AB815
P 6200 5450
F 0 "#PWR014" H 6200 5200 50  0001 C CNN
F 1 "GND" H 6205 5277 50  0000 C CNN
F 2 "" H 6200 5450 50  0001 C CNN
F 3 "" H 6200 5450 50  0001 C CNN
	1    6200 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 5450 6200 5400
Wire Wire Line
	5800 5300 5800 5400
Wire Wire Line
	5800 5400 5900 5400
Connection ~ 6200 5400
Wire Wire Line
	6200 5400 6200 5300
Wire Wire Line
	6100 5300 6100 5400
Connection ~ 6100 5400
Wire Wire Line
	6100 5400 6200 5400
Wire Wire Line
	6000 5300 6000 5400
Connection ~ 6000 5400
Wire Wire Line
	6000 5400 6100 5400
Wire Wire Line
	5900 5300 5900 5400
Connection ~ 5900 5400
Wire Wire Line
	5900 5400 6000 5400
$Comp
L Device:R R-ANS1
U 1 1 6209CBF6
P 950 3350
F 0 "R-ANS1" H 1020 3396 50  0000 L CNN
F 1 "10K" H 1020 3305 50  0000 L CNN
F 2 "" V 880 3350 50  0001 C CNN
F 3 "~" H 950 3350 50  0001 C CNN
	1    950  3350
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR08
U 1 1 6209D8D6
P 950 3050
F 0 "#PWR08" H 950 2900 50  0001 C CNN
F 1 "VDD" H 965 3223 50  0000 C CNN
F 2 "" H 950 3050 50  0001 C CNN
F 3 "" H 950 3050 50  0001 C CNN
	1    950  3050
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW-ANS1
U 1 1 6209E40B
P 1300 3600
F 0 "SW-ANS1" H 1300 3885 50  0000 C CNN
F 1 "SW_Push" H 1300 3794 50  0000 C CNN
F 2 "" H 1300 3800 50  0001 C CNN
F 3 "~" H 1300 3800 50  0001 C CNN
	1    1300 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 6209F314
P 950 3700
F 0 "#PWR09" H 950 3450 50  0001 C CNN
F 1 "GND" H 955 3527 50  0000 C CNN
F 2 "" H 950 3700 50  0001 C CNN
F 3 "" H 950 3700 50  0001 C CNN
	1    950  3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 3600 950  3600
Wire Wire Line
	950  3600 950  3500
Wire Wire Line
	950  3700 950  3600
Connection ~ 950  3600
Wire Wire Line
	950  3050 950  3200
$Comp
L Device:R R-ANS2
U 1 1 620A385B
P 1700 3350
F 0 "R-ANS2" H 1770 3396 50  0000 L CNN
F 1 "10K" H 1770 3305 50  0000 L CNN
F 2 "" V 1630 3350 50  0001 C CNN
F 3 "~" H 1700 3350 50  0001 C CNN
	1    1700 3350
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR010
U 1 1 620A3943
P 1700 3050
F 0 "#PWR010" H 1700 2900 50  0001 C CNN
F 1 "VDD" H 1715 3223 50  0000 C CNN
F 2 "" H 1700 3050 50  0001 C CNN
F 3 "" H 1700 3050 50  0001 C CNN
	1    1700 3050
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW-ANS2
U 1 1 620A394D
P 2050 3600
F 0 "SW-ANS2" H 2050 3885 50  0000 C CNN
F 1 "SW_Push" H 2050 3794 50  0000 C CNN
F 2 "" H 2050 3800 50  0001 C CNN
F 3 "~" H 2050 3800 50  0001 C CNN
	1    2050 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 620A3957
P 1700 3700
F 0 "#PWR011" H 1700 3450 50  0001 C CNN
F 1 "GND" H 1705 3527 50  0000 C CNN
F 2 "" H 1700 3700 50  0001 C CNN
F 3 "" H 1700 3700 50  0001 C CNN
	1    1700 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 3600 1700 3600
Wire Wire Line
	1700 3600 1700 3500
Wire Wire Line
	1700 3700 1700 3600
Connection ~ 1700 3600
Wire Wire Line
	1700 3050 1700 3200
$Comp
L Device:R R-ANS3
U 1 1 620A8BFF
P 2500 3350
F 0 "R-ANS3" H 2570 3396 50  0000 L CNN
F 1 "10K" H 2570 3305 50  0000 L CNN
F 2 "" V 2430 3350 50  0001 C CNN
F 3 "~" H 2500 3350 50  0001 C CNN
	1    2500 3350
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR012
U 1 1 620A8DB3
P 2500 3050
F 0 "#PWR012" H 2500 2900 50  0001 C CNN
F 1 "VDD" H 2515 3223 50  0000 C CNN
F 2 "" H 2500 3050 50  0001 C CNN
F 3 "" H 2500 3050 50  0001 C CNN
	1    2500 3050
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW-ANS3
U 1 1 620A8DBD
P 2850 3600
F 0 "SW-ANS3" H 2850 3885 50  0000 C CNN
F 1 "SW_Push" H 2850 3794 50  0000 C CNN
F 2 "" H 2850 3800 50  0001 C CNN
F 3 "~" H 2850 3800 50  0001 C CNN
	1    2850 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR013
U 1 1 620A8DC7
P 2500 3700
F 0 "#PWR013" H 2500 3450 50  0001 C CNN
F 1 "GND" H 2505 3527 50  0000 C CNN
F 2 "" H 2500 3700 50  0001 C CNN
F 3 "" H 2500 3700 50  0001 C CNN
	1    2500 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 3600 2500 3600
Wire Wire Line
	2500 3600 2500 3500
Wire Wire Line
	2500 3700 2500 3600
Connection ~ 2500 3600
Wire Wire Line
	2500 3050 2500 3200
Text Label 1500 3800 1    50   ~ 0
BTN_A
Wire Wire Line
	2250 3600 2250 3800
Text Label 2250 3800 1    50   ~ 0
BTN_B
Wire Wire Line
	3050 3600 3050 3800
Text Label 3050 3800 1    50   ~ 0
BTN_C
Wire Wire Line
	1500 3600 1500 3800
Wire Wire Line
	6600 2100 6800 2100
Wire Wire Line
	6600 2200 6800 2200
Wire Wire Line
	6600 2300 6800 2300
Wire Wire Line
	6600 2400 6800 2400
Text Label 6800 2100 0    50   ~ 0
LED_RUN
Text Label 6800 2200 0    50   ~ 0
LED_TRUE
Text Label 6800 2300 0    50   ~ 0
LED_FALSE
Text Label 6800 2400 0    50   ~ 0
LED_A
Wire Wire Line
	6600 3500 6800 3500
Text Label 6800 3500 0    50   ~ 0
MMC_NSS
Wire Wire Line
	6600 3700 6800 3700
Wire Wire Line
	6600 3800 6800 3800
Text Label 6800 3700 0    50   ~ 0
LED_B
Text Label 6800 3800 0    50   ~ 0
LED_C
$Comp
L Device:R R-LED-ANS1
U 1 1 620D8F63
P 950 4900
F 0 "R-LED-ANS1" H 1020 4946 50  0000 L CNN
F 1 "330" H 1020 4855 50  0000 L CNN
F 2 "" V 880 4900 50  0001 C CNN
F 3 "~" H 950 4900 50  0001 C CNN
	1    950  4900
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR015
U 1 1 620D9C9C
P 950 4650
F 0 "#PWR015" H 950 4500 50  0001 C CNN
F 1 "VDD" H 965 4823 50  0000 C CNN
F 2 "" H 950 4650 50  0001 C CNN
F 3 "" H 950 4650 50  0001 C CNN
	1    950  4650
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D-ANS-TRUE1
U 1 1 620DA4BD
P 850 5300
F 0 "D-ANS-TRUE1" V 889 5182 50  0000 R CNN
F 1 "LED" V 798 5182 50  0000 R CNN
F 2 "" H 850 5300 50  0001 C CNN
F 3 "~" H 850 5300 50  0001 C CNN
	1    850  5300
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D-ANS-FALSE1
U 1 1 620DA7BA
P 1050 5300
F 0 "D-ANS-FALSE1" V 1089 5182 50  0000 R CNN
F 1 "LED" V 998 5182 50  0000 R CNN
F 2 "" H 1050 5300 50  0001 C CNN
F 3 "~" H 1050 5300 50  0001 C CNN
	1    1050 5300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	850  5450 850  5650
Wire Wire Line
	1050 5450 1050 5650
Wire Wire Line
	950  4650 950  4750
Wire Wire Line
	950  5050 950  5150
Connection ~ 950  5150
Wire Wire Line
	950  5150 850  5150
Wire Wire Line
	1050 5150 950  5150
$Comp
L Device:R R-LED-BTN1
U 1 1 620F399F
P 2000 4900
F 0 "R-LED-BTN1" H 2070 4946 50  0000 L CNN
F 1 "330" H 2070 4855 50  0000 L CNN
F 2 "" V 1930 4900 50  0001 C CNN
F 3 "~" H 2000 4900 50  0001 C CNN
	1    2000 4900
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR016
U 1 1 620F5100
P 2000 4650
F 0 "#PWR016" H 2000 4500 50  0001 C CNN
F 1 "VDD" H 2015 4823 50  0000 C CNN
F 2 "" H 2000 4650 50  0001 C CNN
F 3 "" H 2000 4650 50  0001 C CNN
	1    2000 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D-BTN1
U 1 1 620F5760
P 1850 5350
F 0 "D-BTN1" V 1889 5232 50  0000 R CNN
F 1 "LED" V 1798 5232 50  0000 R CNN
F 2 "" H 1850 5350 50  0001 C CNN
F 3 "~" H 1850 5350 50  0001 C CNN
	1    1850 5350
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D-BTN2
U 1 1 620F655F
P 2000 5350
F 0 "D-BTN2" V 2039 5232 50  0000 R CNN
F 1 "LED" V 1948 5232 50  0000 R CNN
F 2 "" H 2000 5350 50  0001 C CNN
F 3 "~" H 2000 5350 50  0001 C CNN
	1    2000 5350
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D-BTN3
U 1 1 620F6AD7
P 2150 5350
F 0 "D-BTN3" V 2189 5232 50  0000 R CNN
F 1 "LED" V 2098 5232 50  0000 R CNN
F 2 "" H 2150 5350 50  0001 C CNN
F 3 "~" H 2150 5350 50  0001 C CNN
	1    2150 5350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2000 4650 2000 4750
Wire Wire Line
	2000 5050 2000 5150
Wire Wire Line
	2150 5200 2150 5150
Wire Wire Line
	2150 5150 2000 5150
Connection ~ 2000 5150
Wire Wire Line
	2000 5150 2000 5200
Wire Wire Line
	1850 5200 1850 5150
Wire Wire Line
	1850 5150 2000 5150
Text Label 850  5650 1    50   ~ 0
LED_TRUE
Text Label 1050 5650 1    50   ~ 0
LED_FALSE
Wire Wire Line
	1850 5500 1850 5650
Wire Wire Line
	2000 5500 2000 5650
Wire Wire Line
	2150 5500 2150 5650
Text Label 1850 5650 1    50   ~ 0
LED_A
Text Label 2000 5650 1    50   ~ 0
LED_B
Text Label 2150 5650 1    50   ~ 0
LED_C
$Comp
L Device:R R-LED-RUN1
U 1 1 62110B75
P 2750 4900
F 0 "R-LED-RUN1" H 2820 4946 50  0000 L CNN
F 1 "330" H 2820 4855 50  0000 L CNN
F 2 "" V 2680 4900 50  0001 C CNN
F 3 "~" H 2750 4900 50  0001 C CNN
	1    2750 4900
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR017
U 1 1 62111902
P 2750 4650
F 0 "#PWR017" H 2750 4500 50  0001 C CNN
F 1 "VDD" H 2765 4823 50  0000 C CNN
F 2 "" H 2750 4650 50  0001 C CNN
F 3 "" H 2750 4650 50  0001 C CNN
	1    2750 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D-RUN1
U 1 1 62112A2D
P 2750 5350
F 0 "D-RUN1" V 2789 5232 50  0000 R CNN
F 1 "LED" V 2698 5232 50  0000 R CNN
F 2 "" H 2750 5350 50  0001 C CNN
F 3 "~" H 2750 5350 50  0001 C CNN
	1    2750 5350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2750 5050 2750 5200
Wire Wire Line
	2750 4650 2750 4750
Wire Wire Line
	2750 5500 2750 5650
Text Label 2750 5650 1    50   ~ 0
LED_RUN
$Comp
L Connector:Conn_01x05_Male J-STM32-PROG1
U 1 1 62141FCF
P 9300 2850
F 0 "J-STM32-PROG1" H 9408 3231 50  0000 C CNN
F 1 "Conn_01x05_Male" H 9408 3140 50  0000 C CNN
F 2 "" H 9300 2850 50  0001 C CNN
F 3 "~" H 9300 2850 50  0001 C CNN
	1    9300 2850
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR018
U 1 1 621447C6
P 9700 2650
F 0 "#PWR018" H 9700 2500 50  0001 C CNN
F 1 "VDD" H 9715 2823 50  0000 C CNN
F 2 "" H 9700 2650 50  0001 C CNN
F 3 "" H 9700 2650 50  0001 C CNN
	1    9700 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR019
U 1 1 62145589
P 9750 3100
F 0 "#PWR019" H 9750 2850 50  0001 C CNN
F 1 "GND" H 9755 2927 50  0000 C CNN
F 2 "" H 9750 3100 50  0001 C CNN
F 3 "" H 9750 3100 50  0001 C CNN
	1    9750 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 2850 9750 2850
Wire Wire Line
	9750 2850 9750 3100
Wire Wire Line
	9500 2650 9700 2650
Wire Wire Line
	9500 2750 9650 2750
Wire Wire Line
	9500 2950 9650 2950
Text Label 9650 2750 0    50   ~ 0
SWD_CLK
Text Label 9650 2950 0    50   ~ 0
SWD_IO
Wire Wire Line
	9500 3050 9650 3050
Wire Wire Line
	5150 2000 5050 2000
Connection ~ 5150 2000
Text Label 5050 2000 0    50   ~ 0
NRST
Text Label 9650 3050 0    50   ~ 0
NRST
Wire Wire Line
	6600 3300 6800 3300
Wire Wire Line
	6600 3400 6800 3400
Text Label 6800 3300 0    50   ~ 0
SWD_IO
Text Label 6800 3400 0    50   ~ 0
SWD_CLK
$Comp
L Connector:USB_B_Micro J-USB1
U 1 1 621717CB
P 8200 1600
F 0 "J-USB1" H 8257 2067 50  0000 C CNN
F 1 "USB_B_Micro" H 8257 1976 50  0000 C CNN
F 2 "" H 8350 1550 50  0001 C CNN
F 3 "~" H 8350 1550 50  0001 C CNN
	1    8200 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R-USB2
U 1 1 621747E3
P 8800 1600
F 0 "R-USB2" V 8593 1600 50  0000 C CNN
F 1 "68" V 8684 1600 50  0000 C CNN
F 2 "" V 8730 1600 50  0001 C CNN
F 3 "~" H 8800 1600 50  0001 C CNN
	1    8800 1600
	0    1    1    0   
$EndComp
$Comp
L Device:R R-USB3
U 1 1 62175960
P 8800 1700
F 0 "R-USB3" V 8593 1700 50  0000 C CNN
F 1 "68" V 8684 1700 50  0000 C CNN
F 2 "" V 8730 1700 50  0001 C CNN
F 3 "~" H 8800 1700 50  0001 C CNN
	1    8800 1700
	0    1    1    0   
$EndComp
$Comp
L Device:R R-USB1
U 1 1 62175F99
P 8800 1500
F 0 "R-USB1" V 8593 1500 50  0000 C CNN
F 1 "4k7" V 8684 1500 50  0000 C CNN
F 2 "" V 8730 1500 50  0001 C CNN
F 3 "~" H 8800 1500 50  0001 C CNN
	1    8800 1500
	0    1    1    0   
$EndComp
Wire Wire Line
	8650 1600 8600 1600
Wire Wire Line
	8650 1500 8600 1500
Wire Wire Line
	8600 1500 8600 1600
Connection ~ 8600 1600
Wire Wire Line
	8600 1600 8500 1600
Wire Wire Line
	8650 1700 8500 1700
Wire Wire Line
	8950 1600 9050 1600
Text Label 9050 1600 0    50   ~ 0
USB_DP
Wire Wire Line
	8950 1700 9050 1700
Text Label 9050 1700 0    50   ~ 0
USB_DM
$Comp
L power:GND #PWR020
U 1 1 621857BE
P 8100 2100
F 0 "#PWR020" H 8100 1850 50  0001 C CNN
F 1 "GND" H 8105 1927 50  0000 C CNN
F 2 "" H 8100 2100 50  0001 C CNN
F 3 "" H 8100 2100 50  0001 C CNN
	1    8100 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 2000 8100 2100
Wire Wire Line
	8200 2000 8100 2000
Connection ~ 8100 2000
$Comp
L power:VDD #PWR021
U 1 1 6218CA84
P 9050 1500
F 0 "#PWR021" H 9050 1350 50  0001 C CNN
F 1 "VDD" H 9065 1673 50  0000 C CNN
F 2 "" H 9050 1500 50  0001 C CNN
F 3 "" H 9050 1500 50  0001 C CNN
	1    9050 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 1500 9050 1500
Wire Wire Line
	6600 3200 6800 3200
Wire Wire Line
	6600 3100 6800 3100
Text Label 6800 3100 0    50   ~ 0
USB_DM
Text Label 6800 3200 0    50   ~ 0
USB_DP
$Comp
L Connector:Conn_01x03_Male J-UART-ESP321
U 1 1 621A213B
P 8050 2850
F 0 "J-UART-ESP321" H 8158 3131 50  0000 C CNN
F 1 "Conn_01x03_Male" H 8158 3040 50  0000 C CNN
F 2 "" H 8050 2850 50  0001 C CNN
F 3 "~" H 8050 2850 50  0001 C CNN
	1    8050 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 2750 8450 2750
Text Label 8450 2750 0    50   ~ 0
RX0
Wire Wire Line
	8250 2850 8450 2850
Text Label 8450 2850 0    50   ~ 0
TX0
$Comp
L power:GND #PWR025
U 1 1 621AB8B5
P 8450 2950
F 0 "#PWR025" H 8450 2700 50  0001 C CNN
F 1 "GND" H 8455 2777 50  0000 C CNN
F 2 "" H 8450 2950 50  0001 C CNN
F 3 "" H 8450 2950 50  0001 C CNN
	1    8450 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 2950 8450 2950
Wire Wire Line
	6600 3000 6800 3000
Text Label 6800 3000 0    50   ~ 0
TX0
Wire Wire Line
	6600 2900 6800 2900
Text Label 6800 2900 0    50   ~ 0
RX0
$Comp
L codec:MAX98357 U2
U 1 1 621CE07B
P 8550 4800
F 0 "U2" H 8550 5487 60  0000 C CNN
F 1 "MAX98357" H 8550 5381 60  0000 C CNN
F 2 "" H 8550 4800 60  0001 C CNN
F 3 "" H 8550 4800 60  0001 C CNN
	1    8550 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:L L-DAC1
U 1 1 621CF829
P 9450 4400
F 0 "L-DAC1" V 9269 4400 50  0000 C CNN
F 1 "100uH" V 9360 4400 50  0000 C CNN
F 2 "" H 9450 4400 50  0001 C CNN
F 3 "~" H 9450 4400 50  0001 C CNN
	1    9450 4400
	0    1    1    0   
$EndComp
$Comp
L Device:L L-DAC2
U 1 1 621D0590
P 9450 4500
F 0 "L-DAC2" V 9269 4500 50  0000 C CNN
F 1 "100uH" V 9360 4500 50  0000 C CNN
F 2 "" H 9450 4500 50  0001 C CNN
F 3 "~" H 9450 4500 50  0001 C CNN
	1    9450 4500
	0    1    1    0   
$EndComp
Wire Wire Line
	9600 4400 9750 4400
Text Label 9750 4400 0    50   ~ 0
OUTP
Wire Wire Line
	9600 4500 9750 4500
Text Label 9750 4500 0    50   ~ 0
OUTN
Wire Wire Line
	9300 4400 9100 4400
Wire Wire Line
	9300 4500 9100 4500
$Comp
L power:VDD #PWR026
U 1 1 621DEA09
P 9250 4700
F 0 "#PWR026" H 9250 4550 50  0001 C CNN
F 1 "VDD" H 9265 4873 50  0000 C CNN
F 2 "" H 9250 4700 50  0001 C CNN
F 3 "" H 9250 4700 50  0001 C CNN
	1    9250 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 4700 9100 4700
Wire Wire Line
	9100 4800 9250 4800
Wire Wire Line
	9250 4800 9250 4700
Connection ~ 9250 4700
$Comp
L power:GND #PWR027
U 1 1 621E61EA
P 9250 5200
F 0 "#PWR027" H 9250 4950 50  0001 C CNN
F 1 "GND" H 9255 5027 50  0000 C CNN
F 2 "" H 9250 5200 50  0001 C CNN
F 3 "" H 9250 5200 50  0001 C CNN
	1    9250 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 5200 9250 5200
Wire Wire Line
	9100 5100 9250 5100
Wire Wire Line
	9250 5100 9250 5200
Connection ~ 9250 5200
Wire Wire Line
	9100 5000 9250 5000
Wire Wire Line
	9250 5000 9250 5100
Connection ~ 9250 5100
$Comp
L Device:R R-DAC-EN1
U 1 1 621F298A
P 7900 4200
F 0 "R-DAC-EN1" H 7970 4246 50  0000 L CNN
F 1 "1M" H 7970 4155 50  0000 L CNN
F 2 "" V 7830 4200 50  0001 C CNN
F 3 "~" H 7900 4200 50  0001 C CNN
	1    7900 4200
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR024
U 1 1 621F379D
P 7900 3950
F 0 "#PWR024" H 7900 3800 50  0001 C CNN
F 1 "VDD" H 7915 4123 50  0000 C CNN
F 2 "" H 7900 3950 50  0001 C CNN
F 3 "" H 7900 3950 50  0001 C CNN
	1    7900 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 4400 7900 4400
Wire Wire Line
	7900 4400 7900 4350
Wire Wire Line
	7900 3950 7900 4050
Wire Wire Line
	8000 4500 7800 4500
Text Label 7800 4500 0    50   ~ 0
DAC_BCLK
Wire Wire Line
	8000 4600 7800 4600
Text Label 7800 4600 0    50   ~ 0
DAC_LRC
Wire Wire Line
	8000 4700 7800 4700
Text Label 7800 4700 0    50   ~ 0
DAC_DIN
Wire Wire Line
	8000 4900 7800 4900
Text Label 7800 4900 0    50   ~ 0
DAC_GAIN
$Comp
L Device:R R-DAC-GAIN1
U 1 1 6221035F
P 8050 5700
F 0 "R-DAC-GAIN1" V 7843 5700 50  0000 C CNN
F 1 "100K" V 7934 5700 50  0000 C CNN
F 2 "" V 7980 5700 50  0001 C CNN
F 3 "~" H 8050 5700 50  0001 C CNN
	1    8050 5700
	0    1    1    0   
$EndComp
$Comp
L Device:R R-DAC-GAIN2
U 1 1 62211159
P 8050 5800
F 0 "R-DAC-GAIN2" V 7843 5800 50  0000 C CNN
F 1 "100K" V 7934 5800 50  0000 C CNN
F 2 "" V 7980 5800 50  0001 C CNN
F 3 "~" H 8050 5800 50  0001 C CNN
	1    8050 5800
	0    1    1    0   
$EndComp
Wire Wire Line
	8200 5700 8250 5700
Wire Wire Line
	8250 5700 8250 5750
Wire Wire Line
	8250 5800 8200 5800
Wire Wire Line
	8250 5750 8350 5750
Connection ~ 8250 5750
Wire Wire Line
	8250 5750 8250 5800
Text Label 8350 5750 0    50   ~ 0
DAC_GAIN
$Comp
L power:VDD #PWR022
U 1 1 6221B7E4
P 7750 5700
F 0 "#PWR022" H 7750 5550 50  0001 C CNN
F 1 "VDD" H 7765 5873 50  0000 C CNN
F 2 "" H 7750 5700 50  0001 C CNN
F 3 "" H 7750 5700 50  0001 C CNN
	1    7750 5700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR023
U 1 1 6221C036
P 7750 5800
F 0 "#PWR023" H 7750 5550 50  0001 C CNN
F 1 "GND" H 7755 5627 50  0000 C CNN
F 2 "" H 7750 5800 50  0001 C CNN
F 3 "" H 7750 5800 50  0001 C CNN
	1    7750 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 5700 7750 5700
Wire Wire Line
	7900 5800 7750 5800
Wire Wire Line
	6600 4700 6800 4700
Text Label 6800 4700 0    50   ~ 0
DAC_BCLK
Wire Wire Line
	6600 4800 6800 4800
Text Label 6800 4800 0    50   ~ 0
DAC_LRC
Wire Wire Line
	5300 3900 4900 3900
Text Label 4900 3900 0    50   ~ 0
DAC_DIN
$EndSCHEMATC

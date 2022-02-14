EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr User 7087 4724
encoding utf-8
Sheet 1 4
Title "Audiometri Block Sheet"
Date "2022-02-14"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 3750 1900 850  900 
U 620A0EE8
F0 "ESP32" 50
F1 "esp32.sch" 50
F2 "ESP32_TX" O L 3750 2650 50 
F3 "ESP32_RX" I L 3750 2500 50 
F4 "ESP32_VDD" U L 3750 2100 50 
F5 "ESP32_GND" U L 3750 2250 50 
$EndSheet
$Sheet
S 2150 1900 850  900 
U 6218AB3A
F0 "STM32" 50
F1 "stm32.sch" 50
F2 "STM32_TX" O R 3000 2500 50 
F3 "STM32_RX" I R 3000 2650 50 
F4 "STM32_VDD" U R 3000 2100 50 
F5 "STM32_GND" U R 3000 2250 50 
$EndSheet
Wire Wire Line
	3000 2250 3550 2250
Wire Wire Line
	3000 2100 3400 2100
Wire Wire Line
	3000 2500 3750 2500
Wire Wire Line
	3000 2650 3750 2650
$Sheet
S 3750 900  750  650 
U 62169F10
F0 "Voltage Regulator" 50
F1 "vreg.sch" 50
F2 "VREG_VDD" U L 3750 1150 50 
F3 "VREG_GND" U L 3750 1300 50 
$EndSheet
Wire Wire Line
	3750 1300 3550 1300
Wire Wire Line
	3550 1300 3550 2250
Connection ~ 3550 2250
Wire Wire Line
	3550 2250 3750 2250
Wire Wire Line
	3750 1150 3400 1150
Wire Wire Line
	3400 1150 3400 2100
Connection ~ 3400 2100
Wire Wire Line
	3400 2100 3750 2100
$EndSCHEMATC

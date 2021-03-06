EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr User 5906 4134
encoding utf-8
Sheet 4 4
Title "Battery Regulator"
Date "2022-02-14"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Regulator_Linear:AMS1117-3.3 U5
U 1 1 6216A474
P 2600 1300
F 0 "U5" H 2600 1542 50  0000 C CNN
F 1 "AMS1117-3.3" H 2600 1451 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 2600 1500 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 2700 1050 50  0001 C CNN
	1    2600 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:D D-VREG1
U 1 1 6216B802
P 1950 1300
F 0 "D-VREG1" H 1950 1083 50  0001 C CNN
F 1 "D" H 1950 1174 50  0001 C CNN
F 2 "" H 1950 1300 50  0001 C CNN
F 3 "~" H 1950 1300 50  0001 C CNN
	1    1950 1300
	-1   0    0    1   
$EndComp
Wire Wire Line
	2300 1300 2100 1300
$Comp
L power:VDD #PWR045
U 1 1 6216C3D0
P 3050 1300
F 0 "#PWR045" H 3050 1150 50  0001 C CNN
F 1 "VDD" H 3065 1473 50  0000 C CNN
F 2 "" H 3050 1300 50  0001 C CNN
F 3 "" H 3050 1300 50  0001 C CNN
	1    3050 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C-VREG1
U 1 1 6216CAA5
P 3050 1550
F 0 "C-VREG1" H 3165 1596 50  0001 L CNN
F 1 "C" H 3165 1505 50  0001 L CNN
F 2 "" H 3088 1400 50  0001 C CNN
F 3 "~" H 3050 1550 50  0001 C CNN
	1    3050 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 1300 3050 1400
Wire Wire Line
	2900 1300 3050 1300
Connection ~ 3050 1300
$Comp
L Device:C C-VREG2
U 1 1 6216D119
P 3250 1550
F 0 "C-VREG2" H 3365 1596 50  0001 L CNN
F 1 "C" H 3365 1505 50  0001 L CNN
F 2 "" H 3288 1400 50  0001 C CNN
F 3 "~" H 3250 1550 50  0001 C CNN
	1    3250 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 1400 3250 1300
Wire Wire Line
	3250 1300 3050 1300
Wire Wire Line
	3250 1700 3050 1700
Wire Wire Line
	3050 1700 2600 1700
Wire Wire Line
	2600 1700 2600 1600
Connection ~ 3050 1700
$Comp
L Connector:Conn_01x02_Male J-BATTERY1
U 1 1 6216DEB1
P 1500 1300
F 0 "J-BATTERY1" H 1608 1481 50  0001 C CNN
F 1 "Conn_01x02_Male" H 1608 1390 50  0000 C CNN
F 2 "" H 1500 1300 50  0001 C CNN
F 3 "~" H 1500 1300 50  0001 C CNN
	1    1500 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 1300 1700 1300
Wire Wire Line
	1700 1400 2150 1400
Wire Wire Line
	2150 1400 2150 1700
Wire Wire Line
	2150 1700 2600 1700
Connection ~ 2600 1700
$Comp
L power:GND #PWR044
U 1 1 6216FF0D
P 2600 1800
F 0 "#PWR044" H 2600 1550 50  0001 C CNN
F 1 "GND" H 2605 1627 50  0000 C CNN
F 2 "" H 2600 1800 50  0001 C CNN
F 3 "" H 2600 1800 50  0001 C CNN
	1    2600 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 1800 2600 1700
Text HLabel 3750 1300 2    50   UnSpc ~ 0
VREG_VDD
Wire Wire Line
	3750 1300 3250 1300
Connection ~ 3250 1300
Text HLabel 3750 1700 2    50   UnSpc ~ 0
VREG_GND
Wire Wire Line
	3750 1700 3250 1700
Connection ~ 3250 1700
$EndSCHEMATC

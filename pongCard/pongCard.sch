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
L ESP8266:ESP-12E U3
U 1 1 6351AD18
P 9250 1500
F 0 "U3" H 9250 2265 50  0000 C CNN
F 1 "ESP-12E" H 9250 2174 50  0000 C CNN
F 2 "ESP8266:ESP-12E" H 9250 1500 50  0001 C CNN
F 3 "http://l0l.org.uk/2014/12/esp8266-modules-hardware-guide-gotta-catch-em-all/" H 9250 1500 50  0001 C CNN
	1    9250 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 63520128
P 8100 1900
F 0 "R5" V 7893 1900 50  0000 C CNN
F 1 "22k" V 7984 1900 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 8030 1900 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Chip-Resistor-Surface-Mount_RALEC-RTT03223JTP_C103426.html" H 8100 1900 50  0001 C CNN
	1    8100 1900
	0    1    1    0   
$EndComp
$Comp
L Device:Antenna AE1
U 1 1 63520E77
P 10750 950
F 0 "AE1" H 10830 939 50  0000 L CNN
F 1 "Antenna" H 10830 848 50  0000 L CNN
F 2 "TestPoint:TestPoint_Plated_Hole_D2.0mm" H 10750 950 50  0001 C CNN
F 3 "~" H 10750 950 50  0001 C CNN
	1    10750 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	10750 1150 10750 1300
Wire Wire Line
	10750 1300 10550 1300
Wire Wire Line
	10150 1400 10750 1400
Wire Wire Line
	10750 1400 10750 4100
Wire Wire Line
	7200 4100 7200 3400
Wire Wire Line
	8400 3400 8400 4000
Wire Wire Line
	10650 4000 10650 1500
Wire Wire Line
	10650 1500 10150 1500
Wire Wire Line
	7350 3250 7350 2850
Wire Wire Line
	7350 2850 7950 2850
Wire Wire Line
	8550 2850 8550 3250
Connection ~ 7950 2850
Wire Wire Line
	7950 2850 8550 2850
Connection ~ 7950 1900
Wire Wire Line
	7950 1900 7950 2850
Wire Wire Line
	8350 1900 8300 1900
Wire Wire Line
	8400 4000 10650 4000
Wire Wire Line
	7200 4100 10750 4100
Wire Notes Line
	11150 4400 6800 4400
Wire Notes Line
	6800 4400 6800 500 
Text Notes 6900 600  0    50   ~ 0
ESP + Controls
$Comp
L Connector:USB_B_Micro J1
U 1 1 63532CFF
P 850 1850
F 0 "J1" H 907 2317 50  0000 C CNN
F 1 "USB_B_Micro" H 907 2226 50  0000 C CNN
F 2 "Connector_USB:USB_Micro-B_Molex-105017-0001" H 1000 1800 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/USB-Connectors_SHOU-HAN-MicroXNJ_C404969.html" H 1000 1800 50  0001 C CNN
	1    850  1850
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:HT75xx-1-SOT89 U2
U 1 1 63536CBC
P 2400 1750
F 0 "U2" H 2400 2117 50  0000 C CNN
F 1 "HT75xx-1-SOT89" H 2400 2026 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-89-3" H 2400 2075 50  0001 C CIN
F 3 "https://lcsc.com/product-detail/Linear-Voltage-Regulators-LDO_KEXIN-HT7533_C499633.html" H 2400 1850 50  0001 C CNN
	1    2400 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 1950 2400 2050
$Comp
L Device:C C1
U 1 1 63537E59
P 3050 1850
F 0 "C1" H 3165 1896 50  0000 L CNN
F 1 "100u" H 3165 1805 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 3088 1700 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_Samsung-Electro-Mechanics-CL31A107MQHNNNE_C15008.html" H 3050 1850 50  0001 C CNN
	1    3050 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 1650 3050 1650
Wire Wire Line
	3050 1650 3050 1700
Wire Wire Line
	3050 2000 3050 2050
Wire Wire Line
	3050 2050 2400 2050
$Comp
L power:GND #PWR0101
U 1 1 63538DB3
P 3050 2050
F 0 "#PWR0101" H 3050 1800 50  0001 C CNN
F 1 "GND" H 3055 1877 50  0000 C CNN
F 2 "" H 3050 2050 50  0001 C CNN
F 3 "" H 3050 2050 50  0001 C CNN
	1    3050 2050
	1    0    0    -1  
$EndComp
Connection ~ 3050 2050
$Comp
L power:+3V3 #PWR0102
U 1 1 635393F4
P 3050 1650
F 0 "#PWR0102" H 3050 1500 50  0001 C CNN
F 1 "+3V3" H 3065 1823 50  0000 C CNN
F 2 "" H 3050 1650 50  0001 C CNN
F 3 "" H 3050 1650 50  0001 C CNN
	1    3050 1650
	1    0    0    -1  
$EndComp
Connection ~ 3050 1650
Wire Wire Line
	8350 1300 7950 1300
Wire Wire Line
	7950 1300 7950 1900
$Comp
L Device:R R4
U 1 1 6353BDB8
P 7300 1000
F 0 "R4" H 7370 1046 50  0000 L CNN
F 1 "22k" H 7370 955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 7230 1000 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Chip-Resistor-Surface-Mount_RALEC-RTT03223JTP_C103426.html" H 7300 1000 50  0001 C CNN
	1    7300 1000
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0104
U 1 1 6353D00E
P 7300 850
F 0 "#PWR0104" H 7300 700 50  0001 C CNN
F 1 "+3V3" H 7315 1023 50  0000 C CNN
F 2 "" H 7300 850 50  0001 C CNN
F 3 "" H 7300 850 50  0001 C CNN
	1    7300 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 1200 7300 1200
Wire Wire Line
	7300 1200 7300 1150
Wire Wire Line
	850  2250 850  2400
$Comp
L power:+3V3 #PWR0105
U 1 1 6354640C
P 8300 1900
F 0 "#PWR0105" H 8300 1750 50  0001 C CNN
F 1 "+3V3" H 8315 2073 50  0000 C CNN
F 2 "" H 8300 1900 50  0001 C CNN
F 3 "" H 8300 1900 50  0001 C CNN
	1    8300 1900
	1    0    0    -1  
$EndComp
Connection ~ 8300 1900
Wire Wire Line
	8300 1900 8250 1900
$Comp
L power:GND #PWR0106
U 1 1 63547338
P 10150 1900
F 0 "#PWR0106" H 10150 1650 50  0001 C CNN
F 1 "GND" H 10155 1727 50  0000 C CNN
F 2 "" H 10150 1900 50  0001 C CNN
F 3 "" H 10150 1900 50  0001 C CNN
	1    10150 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 2050 1950 2050
Connection ~ 2400 2050
Wire Wire Line
	2100 1650 1950 1650
Text GLabel 10550 1050 1    50   Input ~ 0
Ant
$Comp
L Jumper:SolderJumper_2_Open JP1
U 1 1 637604DA
P 1050 2700
F 0 "JP1" H 1050 2475 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 1050 2566 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 1050 2700 50  0001 C CNN
F 3 "~" H 1050 2700 50  0001 C CNN
	1    1050 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	750  2250 750  2700
Wire Wire Line
	750  2700 900  2700
Wire Wire Line
	1200 2700 1850 2700
Wire Wire Line
	10550 1050 10550 1300
Connection ~ 10550 1300
Wire Wire Line
	10550 1300 10150 1300
Text GLabel 1850 2700 2    50   Input ~ 0
Ant
$Comp
L Device:C C2
U 1 1 6376D403
P 3500 1850
F 0 "C2" H 3615 1896 50  0000 L CNN
F 1 "100nF" H 3615 1805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 3538 1700 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_Walsin-Tech-Corp-0603B104K250CT_C83054.html" H 3500 1850 50  0001 C CNN
	1    3500 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 1650 3500 1650
Wire Wire Line
	3500 1650 3500 1700
Wire Wire Line
	3500 2000 3500 2050
Wire Wire Line
	3500 2050 3050 2050
$Comp
L Device:C C3
U 1 1 637746B2
P 1600 1850
F 0 "C3" H 1715 1896 50  0000 L CNN
F 1 "100u" H 1715 1805 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 1638 1700 50  0001 C CNN
F 3 "~" H 1600 1850 50  0001 C CNN
	1    1600 1850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 63775394
P 1950 1850
F 0 "C4" H 2065 1896 50  0000 L CNN
F 1 "100n" H 2065 1805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1988 1700 50  0001 C CNN
F 3 "~" H 1950 1850 50  0001 C CNN
	1    1950 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 1650 1600 1700
Connection ~ 1600 1650
Wire Wire Line
	1600 1650 1150 1650
Wire Wire Line
	1950 1650 1950 1700
Connection ~ 1950 1650
Wire Wire Line
	1950 1650 1600 1650
Wire Wire Line
	1950 2050 1950 2000
Connection ~ 1950 2050
Wire Wire Line
	1600 2050 1600 2000
Wire Wire Line
	1600 2050 1400 2050
Wire Wire Line
	1400 2050 1400 2400
Connection ~ 1600 2050
Wire Wire Line
	1400 2400 850  2400
Wire Wire Line
	1600 2050 1950 2050
$Comp
L Device:R_POT_MountingPin RV1
U 1 1 63796DB6
P 7200 3250
F 0 "RV1" H 7394 3296 50  0000 L CNN
F 1 "10k" H 7394 3205 50  0000 L CNN
F 2 "pongCard:linearPotentiometer" H 7200 3250 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Variable-Resistors-Potentiometers_ALPSALPINE-RS30H11AAA02_C470614.html" H 7200 3250 50  0001 C CNN
	1    7200 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT_MountingPin RV2
U 1 1 63798551
P 8400 3250
F 0 "RV2" H 8594 3296 50  0000 L CNN
F 1 "10k" H 8594 3205 50  0000 L CNN
F 2 "pongCard:linearPotentiometer" H 8400 3250 50  0001 C CNN
F 3 "https://lcsc.com/product-detail/Variable-Resistors-Potentiometers_ALPSALPINE-RS30H11AAA02_C470614.html" H 8400 3250 50  0001 C CNN
	1    8400 3250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 637A4F2E
P 7000 3250
F 0 "#PWR?" H 7000 3000 50  0001 C CNN
F 1 "GND" H 7005 3077 50  0000 C CNN
F 2 "" H 7000 3250 50  0001 C CNN
F 3 "" H 7000 3250 50  0001 C CNN
	1    7000 3250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 637A5680
P 8200 3250
F 0 "#PWR?" H 8200 3000 50  0001 C CNN
F 1 "GND" H 8205 3077 50  0000 C CNN
F 2 "" H 8200 3250 50  0001 C CNN
F 3 "" H 8200 3250 50  0001 C CNN
	1    8200 3250
	1    0    0    -1  
$EndComp
$EndSCHEMATC

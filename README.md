# 3D-Printer-Controller-CrowPanel-HMI
Work in Progress, HMI screen for Marlin Firmware. Grok designed and programed.

## Hardware

Display: CrowPanel ESP32-S3 7" (800×480 RGB Parallel IPS)
Controller: BTT Octopus 1.1
Communication: UART (250000 baud)
Touch: GT911 + PCA9557 (properly reset)

## Key Features Implemented

Main Menu – Central navigation hub
Print Status Screen – Live temps, progress, layer info, speed override, baby Z
Jog Screen – Full directional control + Auto Z Align (G34) + Auto Bed Level (G29)
TMC5160 Settings – Live current, microsteps, hybrid threshold, StallGuard tuning
Filament Management – Runout & Jam sensor control with status indicators
File Browser – SD card navigation, select & print
Settings Screen – Live reading of steps (M92), flow (M221), brightness, Auto PID tuning
About Screen – System information

## Technology Stack

MCU: ESP32-S3
GUI: LVGL 8.3.11 + SquareLine Studio
Display Driver: LovyanGFX (RGB Parallel + DMA)
Touch: GT911 with PCA9557 reset
Build System: PlatformIO
Communication: Full bidirectional G-code parser

##Status

NOT yet Fully functional
LVGL 8.3.11 stable version
PCA9557 touch reset implemented
Live data syncing from Marlin

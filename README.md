
# 3D-Printer-Controller-CrowPanel-HMI
Work in Progress, HMI screen for Marlin Firmware. Grok designed and programed.

<img width="910" height="594" alt="MainScreen" src="https://github.com/user-attachments/assets/2dbb841f-3bcd-4b0a-a691-23871268fcf3" />

<img width="906" height="590" alt="PrintingScreen" src="https://github.com/user-attachments/assets/b278bf1f-5c5c-4cd2-a7e5-626ac3ba3cc6" />

<img width="908" height="598" alt="JoggingScreen" src="https://github.com/user-attachments/assets/1cd0ecfd-3993-4514-bbec-7b64a62e7848" />

<img width="911" height="597" alt="TMCScreen" src="https://github.com/user-attachments/assets/164e09de-980b-4ed3-adc4-8aee14898a91" />

<img width="910" height="592" alt="FilamentScreen" src="https://github.com/user-attachments/assets/27c2b02b-6efc-491b-88b9-5dd67b7efd14" />

<img width="905" height="590" alt="FilesScreen" src="https://github.com/user-attachments/assets/77b508f5-dfe4-417b-89dd-b06e6373a2ca" />

<img width="908" height="586" alt="SettingsScreen" src="https://github.com/user-attachments/assets/6487c5b5-3dd7-4f20-a615-528692e4e5af" />

<img width="912" height="588" alt="AboutScreen" src="https://github.com/user-attachments/assets/db2ebdc9-cc0b-4516-b527-05dd7fbaa3c3" />

<img width="905" height="590" alt="TemperatureScreen" src="https://github.com/user-attachments/assets/39c97951-6dda-480e-993e-83f08a86b5a2" />


working display screens installed using CrowPanel_Marlin_HMI Esp install and flash.zip

work to do:  get ui.h and ui_events.c  etc... into build and recompile to comunicate to marlin firmware.

















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

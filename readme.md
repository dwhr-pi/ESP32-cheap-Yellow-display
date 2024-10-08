# Projects for the ESP32-2432S028R aka "Cheap Yellow Display" (CYD)
Arduino projects using the ESP32-2432S028R aka "Cheap Yellow Display" or CYD  
Programable from Arduino IDE, MicroPython, ESP-ID  

[ESP32 Dev Board – 2.8 inch 240×320 Smart Display TFT with Touchscreen CYD – “Cheap Yellow Display” (ESP32-2432S028R)](https://makeradvisor.com/tools/cyd-cheap-yellow-display-esp32-2432s028r/)  
Also available from AliExpress in 2.8" for ~$10 or 5"(?) for ~$35.

#### [ESP32-WROOM-32 module](https://www.espressif.com/en/products/modules/esp32)
  - ESP32-D0WD Dual-core Tensilica Xtensa LX6 MCU, integrated WI-FI and Bluetooth stacks.
    - 520KB SRAM, 448KB ROM, 4MB Flash (no PSRAM)
    - max Frequency: 240MHz
#### Module components
  - 2.8 inch color TFT display screen with ILI9341 driver chip
    - Display resolution: 240x320px with resistive touch screen
    - Backlight control
  - TF card interface for external storage
  - Serial interface
  - Temperature and humidity sensor interface (DHT11 interface) and reserved IO port interface  
  - powered from 5V micro USB, power consumption: ~115mA
  - size: 50.0×86.0mm, weight: ~50g
#### I/O Connections
The RGB LED is connected to: red (GPIO 4), green (GPIO 16), and blue (GPIO 17).  
Speaker on a 2P 1.25mm JST connector, controlled by GPIO 26.  
LDR (Light Dependent Resistor) on GPIO 34.  
There are two extended GPIO connectors labeled P3 and CN1 on the board with 4 GPIOs available: GPIO 35, GPIO 22, GPIO 21, and GPIO 27.

###### P3 Extended IO
GND, GPIO 35, GPIO 22, and GPIO 21.  
Realistically, only GPIO35 is usable since GPIO 22 is on the CN1 I2C connector and GPIO 21 is used for the display backlight. If the backlight is on, GPIO 21 will be on.  

###### CN1 Extended IO
GND, GPIO 22, GPIO 27 and 3V3 pins. 
GPIO22 is also available on the P3 connector. Pins on CN1 can be used to connect to I2C devices.  

###### P1 TX/RX
GPIO 1 — TX, GPIO 3 — RX  
Used for serial communication and connected directly to the CH340 (USB to serial converter).  
Cannot be used with other peripherals (like a GPS module), likely because of the connection to the CH340.  

### Additional information
- [Getting Started Guide for the ESP32 Cheap Yellow Display ](https://randomnerdtutorials.com/cheap-yellow-display-esp32-2432s028r/)
- [ESP32 Cheap Yellow Display (CYD) Pinout](https://randomnerdtutorials.com/esp32-cheap-yellow-display-cyd-pinout-esp32-2432s028r/)
- [LVGL with ESP32 Cheap Yellow Display Board](https://randomnerdtutorials.com/lvgl-cheap-yellow-display-esp32-2432s028r/)

## Arduino Configuration
#### required libraries
["TFT_eSPI" library by Bodmer](https://github.com/Bodmer/TFT_eSPI) requires specific configuration of User_Setup.h or download from https://RandomNerdTutorials.com/cyd/  
["XPT2046_Touchscreen" library by Paul Stoffregen](https://github.com/PaulStoffregen/XPT2046_Touchscreen)  
both of these can be searched for from the Arduino library manager.  
#### custom User_Setup.h
download from https://github.com/RuiSantosdotme/ESP32-TFT-Touchscreen/raw/main/configs/User_Setup.zip and replace library copy in TFT_eSPI library.
#### Board configuration
ESP32 -> ESP32 Dev Module

## Projects

### ESP32-Cheap-yellow-display-test
Arduino project copied from [Getting Started with ESP32 Cheap Yellow Display Board – CYD (ESP32-2432S028R)](https://randomnerdtutorials.com/cheap-yellow-display-esp32-2432s028r/) by Rui Santos & Sara Santos at Random Nerd Tutorials.  
demos display and touch capabilities. - works! 

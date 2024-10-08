/*
from https://forum.arduino.cc/t/esp32-2432s028r-all-in-one-display-touch-spi-problems/1059746/21
------------------------------------------------
This sketch tests and demonstrates the use of touchscreen functions of the ESP32 Smart Display
ESP32-2432S028 using the TFT_eTouch.h library available on GitHub: https://github.com/achillhasler/TFT_eTouch. 
The smart display uses different SPI pins for the touchscreen controller and for the the TFT display 
controller ILI9341. This means that the touch capabilities of the TFT_eSPI library cannot be used as 
this library assumes same SPI pins for touchscreen and display.

Using the TFT_eTouch library allows the touch controller to use different SPI pins from the display.

This sketch reads the touch display displays the screen location touched.

The calibration settings were obtained from running the calibrate.ino sketch
with the ESP32-2432S028 display.

------------------------------------------------------------------------------------------------------
*/

#include <TFT_eTouch.h>
#include <TFT_eSPI.h>
#include <User_Setup.h> // User Setup ESP32 ILI9341 used by ESP32-2432S028 display
#include "Free_Fonts.h"
#include <SPI.h>

// TFT display defines are in the TFT_eSPI UserSetup.h

//defines related to ESP32 Smart Display
//--------- TFT_eTouch defines --------
// pins used by ESP32-2432S028 display touch controller
#define ETOUCH_MOSI 32
#define ETOUCH_MISO 39
#define ETOUCH_SCK 25
#define ETOUCH_CS 33
#define ETOUCH_IRQ 0xff // not used in this sketch
//
//---- TFT defines not defined in TFT_eSPI.h : User_Setup.h
#define SCREEN_ROTATION 1
#define TFT_BL 21

SPIClass hSPI(HSPI);//define SPI port to be used by TFT_eTouch
TFT_eSPI tft; // TFT_eSPI instance
TFT_eTouch<TFT_eSPI> touch(tft, ETOUCH_CS, ETOUCH_IRQ, hSPI);

//variables used by Sketch
int tft_width;
int tft_height;

void setup()
{
    // put your setup code here, to run once
    Serial.begin(115200);
    hSPI.begin(ETOUCH_SCK, ETOUCH_MISO, ETOUCH_MOSI, ETOUCH_CS);// Touch controller pins
    tft.begin();
    touch.init();
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
    tft.setRotation(SCREEN_ROTATION);
    tft.fillScreen(TFT_BLACK);
    tft_width = tft.width();
    tft_height = tft.height();
    tft.setTextColor(TFT_WHITE);
    tft.setFreeFont(FM12);
// the following Calibration was obtained using calibrate.ino in TFT_eTouch.h examples
    TFT_eTouchBase::Calibation calibation = { 233, 3785, 3731, 120, 2 };
    touch.setCalibration(calibation);
}

void loop()
{

    static uint32_t last_update = 0;
    if (last_update + touch.getMeasureWait() > millis()) return;
    last_update = millis();
    static bool is_touched = false;
    int16_t x, y; // screen coordinates
    if (touch.getXY(x, y))
    {
        if (!is_touched)   // we have pen down!
        {
            is_touched = true;
            tft.fillScreen(TFT_BLACK);
            Serial.print("Touched!!    ");
            Serial.print("At X= ");
            Serial.print(x);
            Serial.print(" Y= ");
            Serial.println(y);
            tft.drawCentreString("Touched", tft_width / 2, tft_height / 2, GFXFF);
            String display_position = "X= " + String(x) + " Y=" + String (y);
            tft.drawCentreString(display_position, tft_width / 2, tft_height / 2 + 20, GFXFF);
            tft.setTextPadding(tft.textWidth("+", GFXFF));
            tft.drawString("+", x, y, GFXFF);
        }
        else
        {
            if (is_touched)   // we have pen up!
            {
                is_touched = false;
                touch.reset();
            }
        }

    }
}
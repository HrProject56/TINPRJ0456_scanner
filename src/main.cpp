#include <Arduino.h>
#include <Wire.h>
#include "ColorSensor.hpp"
#include "display.hpp"
#include "Communication.hpp"

// #if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
// #error Bluetooth is not enabled! Please run 'make menuconfig' to and enable it
// #endif


ColorSensor cs;
OledDisplay od;
Communication com;


bool scanFlag = false;
uint16_t *colorArray = nullptr;


/**
 * Start and configure our:
 * - Serial connection
 * - TCS34725 Color sensor
 */
void setup() {
    Serial.begin(115200);

    // Init display
    od.initDisplay();

    com.commInit();
    cs.setColorSensor();
    // Serial.println(WiFi.macAddress());
}

/**
 * Refresh data
 */
void loop() {
    if (scanFlag) {
        colorArray = cs.getColor();
        od.writeStringToDisplay("SCAN");
    } else {
        od.writeStringToDisplay("READY");
    }
//    com.writeBT(color);
    com.commRead();
    Serial.println("Hi");;
    delay(1000);
}
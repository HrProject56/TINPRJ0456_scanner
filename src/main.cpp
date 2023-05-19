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


/**
 * Start and configure our:
 * - Serial connection
 * - TCS34725 Color sensor
 */
void setup() {
    Serial.begin(115200);

    // Init display
    od.initDisplay();
    od.writeStringToDisplay("yo mama");

    com.commInit();
    cs.setColorSensor();
    // Serial.println(WiFi.macAddress());
}

/**
 * Refresh data
 */
void loop() {
    unsigned short * color = cs.getColor();
//    com.writeBT(color);
    com.commRead();
    Serial.println("Hi");
    delay(1000);
}
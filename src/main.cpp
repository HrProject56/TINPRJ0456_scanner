#include <Wire.h>
#include <WiFi.h>
#include "Communication/Communication.h"
#include "ColorSensor/ColorSensor.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run 'make menuconfig' to and enable it
#endif

Communication com;
ColorSensor cs;

/**
 * Start and configure our:
 * - Serial connection
 * - TCS34725 Color sensor
 */
void setup() {
    Serial.begin(115200);
    com.setBT();
    cs.setColorSensor();
    Serial.println(WiFi.macAddress());
}

/**
 * Refresh data
 */
void loop() {
//    unsigned short * color = cs.getColor();
//    com.writeBT(color);
    Serial.println("Hi");
    delay(1000);
}
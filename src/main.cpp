#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "ColorSensor.hpp"

// #if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
// #error Bluetooth is not enabled! Please run 'make menuconfig' to and enable it
// #endif

TwoWire *wire1 = new TwoWire(6, 7);
ColorSensor cs;
Adafruit_SSD1306 display(128, 64, wire1, -1);


/**
 * Start and configure our:
 * - Serial connection
 * - TCS34725 Color sensor
 */
void setup() {
    Serial.begin(115200);

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 allocation failed"));
        for(;;) Serial.println("Display doesn't work"); // Don't proceed, loop forever
    } 

    delay(2000);
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    // Display static text
    display.println("Hello, world!");
    display.display();

    // com.setBT();
    cs.setColorSensor();
    // Serial.println(WiFi.macAddress());
}

/**
 * Refresh data
 */
void loop() {
    unsigned short * color = cs.getColor();
//    com.writeBT(color);
    Serial.println("Hi");
    delay(1000);
}
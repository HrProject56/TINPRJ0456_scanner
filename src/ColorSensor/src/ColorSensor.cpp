//
// Created by rwfli on 08/11/2022.
//
#include "ColorSensor.h"
#include "../../../lib/Adafruit_BusIO/Adafruit_I2CDevice.h"
#include "../../../lib/Adafruit_BusIO/Adafruit_SPIDevice.h"
#include "../../../lib/Adafruit_TCS34725/Adafruit_TCS34725.h"

extern HardwareSerial Serial;

// Define our color sensor
Adafruit_TCS34725 tcs;

/**
 * Setup colour sensor - TCS34725
 * TCS34725 - ESP32e
 * SDA -> SDA (pin 21)
 * SCL -> SCL (pin 22)
 * GND -> GND
 * VIN -> VCC of een 3v3 pin
 */
void ColorSensor::setColorSensor() {
    tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X); // TCS34725_GAIN_4X or TCS34725_GAIN_1X`
    if (tcs.begin()) {
        Serial.println("Found sensor");
    } else {
        Serial.println("No TCS34725 found ... check your connections and reset the ESP");
        while (1);
    }
}

/**
 * Get/update the current colour
 */
int * ColorSensor::getColor() {
    // Create unsigned variables to store our values in
    uint16_t r, g, b, c, colorTemp, lux;
    static int a[6];

    tcs.getRawData(&r, &g, &b, &c);             // Request the RGBC data
    colorTemp = tcs.calculateColorTemperature(r, g, b);     // Calculate the color temp
    lux = tcs.calculateLux(r, g, b);                        // Calculate LUX

    a[0] = r;
    a[1] = g;
    a[2] = b;
    a[3] = c;
    a[4] = colorTemp;
    a[5] = lux;

    Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
    Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
    Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
    Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
    Serial.print("TEMP: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
    Serial.print("LUX: "); Serial.print(lux, DEC); Serial.print(" - ");
    Serial.println(" -> Now sending to specified Bluetooth function! ");

    auto res = a;
    return res;
}
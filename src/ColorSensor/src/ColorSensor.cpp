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
    tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X); // TCS34725_GAIN_4X or TCS34725_GAIN_1X`
    if (tcs.begin()) {
        Serial.println("Found sensor");
    } else {
        Serial.println("No TCS34725 found ... check your connections and reset the ESP");
        while (1);
    }
}

/**
 * Get/change the current colour
 */
std::initializer_list<unsigned short> ColorSensor::getColor() {
    // Create unsigned variables to store our values in
    uint16_t r, g, b, c, colorTemp, lux;

    tcs.getRawData(&r, &g, &b, &c);             // Request the RGBC data
    colorTemp = tcs.calculateColorTemperature(r, g, b);     // Calculate the color temp
    lux = tcs.calculateLux(r, g, b);                        // Calculate LUX

    auto res = {r, g, b, c, colorTemp, lux};
    return res;
}
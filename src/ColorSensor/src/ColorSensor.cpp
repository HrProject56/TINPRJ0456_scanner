//
// Created by rwfli on 08/11/2022.
//
#include <iostream>
#include "ColorSensor.h"
#include "../../../lib/Adafruit_BusIO/Adafruit_I2CDevice.h"
#include "../../../lib/Adafruit_BusIO/Adafruit_SPIDevice.h"
#include "../../../lib/Adafruit_TCS34725/Adafruit_TCS34725.h"

extern HardwareSerial Serial;

// Define our color sensor
Adafruit_TCS34725 tcs;

const int a_size = 7; // Array size
uint16_t prop[a_size];

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
//    tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

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
uint16_t * ColorSensor::getColor() {
    try {
        // Properties
        int a_size_pos = 0, r = 1, g = 2, b = 3, c = 4, colorTemp = 5, lux = 6; // Position in array

        // Store our color through an unsigned variable
        memset(prop, 0, a_size*sizeof(int));
        prop[a_size] = {}; // 0: a_size, 1:r, 2:g, 3:b, 4:c, 5:temp, 6:lux
        prop[0] = a_size;

        // Calculate our color
        tcs.getRawData(&prop[r], &prop[g], &prop[b], &prop[c]);                    // Request the RGBC data
        prop[4] = tcs.calculateColorTemperature(prop[r], prop[g], prop[b]);           // Calculate the color temp
        prop[5] = tcs.calculateLux(prop[r], prop[g], prop[b]);                        // Calculate LUX

        // Print colors
        printColor((int) prop[r], (int) prop[g], (int) prop[b], (int) prop[c], (int) prop[colorTemp], (int) prop[lux], (int) prop[a_size_pos]);

    } catch (std::exception &e) {
        std::cout << " a standard exception was caught, with message '" << e.what() << "'\n";
    }
    return prop;
}

/**
 * Print current colors
 * @param r
 * @param g
 * @param b
 * @param c
 * @param temp
 * @param lux
 * @param a_size
 */
void ColorSensor::printColor(int r, int g, int b, int c, int temp, int lux, int a_size) {
    Serial.print("R: ");
    Serial.print(r, DEC);
    Serial.print(" G: ");
    Serial.print(g, DEC);
    Serial.print(" B: ");
    Serial.print(b, DEC);
    Serial.print(" C: ");
    Serial.print(c, DEC);
    Serial.print(" TEMP: ");
    Serial.print(temp, DEC);
    Serial.print(" K - ");
    Serial.print("LUX: ");
    Serial.print(lux, DEC);
    Serial.print(" - ");
    Serial.print("Array Size: ");
    Serial.print(a_size, DEC);
    Serial.println(" -> Now sending to specified Bluetooth function! ");
}
#include <Wire.h>
#include "../lib/Adafruit_BusIO/Adafruit_I2CDevice.h"
#include "../lib/Adafruit_BusIO/Adafruit_SPIDevice.h"
#include "../lib/Adafruit_TCS34725/Adafruit_TCS34725.h"

// Define our color sensor
Adafruit_TCS34725 tcs;

// Signatures
void setColorSensor();

void getColor();

/**
 * Start and configure our:
 * - Serial connection
 * - TCS34725 Color sensor
 */
void setup() {
    Serial.begin(115200);
    setColorSensor();
}

/**
 * Refresh data
 */
void loop() {
    getColor();
}

/**
 * Setup colour sensor - TCS34725
 * TCS34725 - ESP32e
 * SDA -> SDA (pin 21)
 * SCL -> SCL (pin 22)
 * GND -> GND
 * VIN -> VCC of een 3v3 pin
 */
void setColorSensor() {
    tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X); // TCS34725_GAIN_4X or TCS34725_GAIN_1X

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
void getColor() {
    // Create unsigned variables to store our values in
    uint16_t r, g, b, c, colorTemp, lux;

    tcs.getRawData(&r, &g, &b, &c);             // Request the RGBC data
    colorTemp = tcs.calculateColorTemperature(r, g, b);     // Calculate the color temp
    lux = tcs.calculateLux(r, g, b);                        // Calculate LUX

    Serial.print("Color Temp: ");
    Serial.print(colorTemp, DEC);
    Serial.print(" K - ");
    Serial.print("Lux: ");
    Serial.print(lux, DEC);
    Serial.print(" - ");
    Serial.print("R: ");
    Serial.print(r, DEC);
    Serial.print(" ");
    Serial.print("G: ");
    Serial.print(g, DEC);
    Serial.print(" ");
    Serial.print("B: ");
    Serial.print(b, DEC);
    Serial.print(" ");
    Serial.print("C: ");
    Serial.print(c, DEC);
    Serial.print(" ");
    Serial.println(" ");
}
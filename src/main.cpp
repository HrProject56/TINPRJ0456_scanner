#include <Wire.h>
#include <WiFi.h>
#include "../lib/BluetoothSerial/src/BluetoothSerial.h"
#include "../lib/Adafruit_BusIO/Adafruit_I2CDevice.h"
#include "../lib/Adafruit_BusIO/Adafruit_SPIDevice.h"
#include "../lib/Adafruit_TCS34725/Adafruit_TCS34725.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run 'make menuconfig' to and enable it
#endif

// Define Bluetooth serial
BluetoothSerial SerialBT;

// Define our color sensor
Adafruit_TCS34725 tcs;

// Signatures
void setColorSensor();

std::initializer_list<unsigned short> getColor();

/**
 * Start and configure our:
 * - Serial connection
 * - TCS34725 Color sensor
 */
void setup() {
    Serial.begin(115200);
    SerialBT.begin("ColorSensor");
    setColorSensor();
    Serial.println(WiFi.macAddress());
}

/**
 * Refresh data
 */
void loop() {
    auto color= getColor();

    auto r = (String) color.begin()[0];
    auto g = (String) color.begin()[1];
    auto b = (String) color.begin()[2];
    auto c = (String) color.begin()[3];
    auto temp = (String) color.begin()[4];
    auto lux = (String) color.begin()[5];

    String a = "R: " + r + ", G: " + g + ", B: " + b + ", C: " + c + ", TEMP: " + temp + ", LUX" + lux;
    uint8_t buf[a.length()];
    memcpy(buf,a.c_str(),a.length());
    SerialBT.write(buf,a.length());
    SerialBT.println();

    if (Serial.available()){
        SerialBT.write(Serial.read());
    }

    if (SerialBT.available()){
        Serial.write(SerialBT.read());
    }
    delay(1000);
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
std::initializer_list<unsigned short> getColor() {
    // Create unsigned variables to store our values in
    uint16_t r, g, b, c, colorTemp, lux;

    tcs.getRawData(&r, &g, &b, &c);             // Request the RGBC data
    colorTemp = tcs.calculateColorTemperature(r, g, b);     // Calculate the color temp
    lux = tcs.calculateLux(r, g, b);                        // Calculate LUX

    // Print the values to the serial monitor
//    Serial.print("RAW R: ");
//    Serial.print(r, DEC);
//    Serial.print(" ");
//    Serial.print("G: ");
//    Serial.print(g, DEC);
//    Serial.print(" ");
//    Serial.print("B: ");
//    Serial.print(b, DEC);
//    Serial.println(" ");

//    if (r >= 255 && g >= 255 && b >= 255) {
//        Serial.println("White");
//    } else if (r >= 255 && g >= 255 && b <= 255) {
//        Serial.println("Yellow");
//    } else if (r >= 255 && g <= 255 && b <= 255) {
//        Serial.println("Red");
//    } else if (r <= 255 && g >= 255 && b <= 255) {
//        Serial.println("Green");
//    } else if (r <= 255 && g <= 255 && b >= 255) {
//        Serial.println("Blue");
//    } else if (r <= 0 && g <= 0 && b <= 0) {
//        Serial.println("Black");
//    } else {
//        Serial.println("Unknown");
//    }

//    Serial.print("Color Temp: ");
//    Serial.print(colorTemp, DEC);
//    Serial.print(" K - ");
//    Serial.print("Lux: ");
//    Serial.print(lux, DEC);
//    Serial.print(" - ");
//    Serial.print("R: ");
//    Serial.print(r, DEC);
//    Serial.print(" ");
//    Serial.print("G: ");
//    Serial.print(g, DEC);
//    Serial.print(" ");
//    Serial.print("B: ");
//    Serial.print(b, DEC);
//    Serial.print(" ");
//    Serial.print("C: ");
//    Serial.print(c, DEC);
//    Serial.print(" ");
//    Serial.println(" ");

    auto res = {r, g, b, c, colorTemp, lux};
    return res;
}
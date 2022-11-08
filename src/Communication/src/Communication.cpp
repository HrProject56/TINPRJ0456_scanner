//
// Created by rwfli on 08/11/2022.
//

#include "Communication.h"
#include "../../../lib/BluetoothSerial/src/BluetoothSerial.h"

extern HardwareSerial Serial;
extern BluetoothSerial SerialBT;

void Communication::setBT() {
    SerialBT.begin("ColorSensor");
    return;
}

void Communication::writeBT(std::initializer_list color) {
    auto r = (String) color.begin()[0];
    auto g = (String) color.begin()[1];
    auto b = (String) color.begin()[2];
    auto c = (String) color.begin()[3];
    auto temp = (String) color.begin()[4];
    auto lux = (String) color.begin()[5];

    String a = "R: " + r + ", G: " + g + ", B: " + b + ", C: " + c + ", TEMP: " + temp + ", LUX" + lux;
    uint8_t buf[a.length()];
    memcpy(buf, a.c_str(), a.length());
    SerialBT.write(buf, a.length());
    SerialBT.println();

    if (SerialBT.connected()) {
        if (Serial.available()) {
            SerialBT.write(Serial.read());
        }

        if (SerialBT.available()) {
            Serial.write(SerialBT.read());
        }
    }
}

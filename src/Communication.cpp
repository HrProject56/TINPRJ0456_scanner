// //
// // Created by rwfli on 08/11/2022.
// //

#include <Arduino.h>
#include <iostream>
#include "Communication.hpp"
#include <Wire.h>


#define W_SSID "Ziggo5573389-gast"
#define W_PASSWORD "Flinterman1!"

#define MAX_TIMEOUT 10


void Communication::commInit()
{
    this->_wire = new TwoWire(0, 1);
    this->_wire->begin();



    // WiFi.begin(W_SSID, W_PASSWORD);
    // Serial.print("Connecting: ");
    // int c = 0;
    // while (WiFi.status() != WL_CONNECTED) {
    //     Serial.print("...");
    //     c++;

    //     if (c >= MAX_TIMEOUT) return;
    //     delay(1000);
    // }
    // Serial.println(" connected!!");
}


void Communication::commWrite(unsigned short &list)
{
    
}


void Communication::commRead()
{
    String message = "yomama";

    this->_wire->beginTransmission(8);
    for (int i = 0; message[i] != '\0'; i++) {
        Wire.write(message[i]); // Send each character of the message
    }
    this->_wire->endTransmission();
}
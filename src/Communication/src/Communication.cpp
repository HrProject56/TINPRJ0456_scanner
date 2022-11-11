//
// Created by rwfli on 08/11/2022.
//

#include <Arduino.h>
#include "Communication.h"
#include "../../../lib/ESP32_BLE_Arduino-1.0.1/src/BLEDevice.h"
#include "../../../lib/ESP32_BLE_Arduino-1.0.1/src/BLEUtils.h"
#include "../../../lib/ESP32_BLE_Arduino-1.0.1/src/BLEServer.h"
#include "../../../lib/ESP32_BLE_Arduino-1.0.1/src/BLE2902.h"
//#include "../../../lib/BluetoothSerial/src/BluetoothSerial.h"

extern HardwareSerial Serial;

#define SERVICE_UUID        "d6960225-2fbc-4565-bf52-0f1cc61bbfcf"
#define CHARACTERISTIC_UUID "13d258f5-80c4-4863-a995-53604358e2e5"

BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristic = NULL;

bool deviceConnected;
bool oldDeviceConnected;

uint32_t value = 0;

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer *pServer) {
        deviceConnected = true;
        Serial.println("New connection detected: " + pServer->getConnId());
    };

    void onDisconnect(BLEServer *pServer) {
        deviceConnected = false;
        Serial.println("Connection dropped..");
    }
};

void Communication::setBT() {
    deviceConnected = false;
    oldDeviceConnected = false;
    value = 0;

    // Create the BLE Device
    BLEDevice::init("ColorSensor");

    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    // Create the BLE Service
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // Create a BLE Characteristic
    pCharacteristic = pService->createCharacteristic(
            CHARACTERISTIC_UUID,
            BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE |
            BLECharacteristic::PROPERTY_NOTIFY |
            BLECharacteristic::PROPERTY_INDICATE
    );

    // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
    // Create a BLE Descriptor
    pCharacteristic->addDescriptor(new BLE2902());

    // Start the service
    pService->start();

    // Start advertising
    pServer->getAdvertising()->start();
//    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
//    pAdvertising->addServiceUUID(SERVICE_UUID);
//    pAdvertising->setScanResponse(false);
//    pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
//    BLEDevice::startAdvertising();
}

void Communication::writeBT(int *list) {
    int *color = list;
    String r = (String) color[0];
    String g = (String) color[1];
    String b = (String) color[2];
    String c = (String) color[3];
    String temp = (String) color[4];
    String lux = (String) color[5];

//    auto a = "R: " + r + ", G: " + g + ", B: " + b + ", C: " + c + ", TEMP: " + temp + ", LUX: " + lux;
//    Serial.println(a);

    uint8_t val2[3] = {254, 0, 0};
    pCharacteristic->setValue((uint8_t *) &val2, 3);
    pCharacteristic->notify();

    uint8_t val3[5] = {'R', 'U', 'B', 'E', 'N'};
    pCharacteristic->setValue((uint8_t *) &val3, 5);
    pCharacteristic->notify();

    // notify changed value
    if (deviceConnected) {
        Serial.println("Device connected!");

//        pCharacteristic->setValue((uint8_t *) &value, 4);
//        pCharacteristic->notify();
//        value++;
        delay(3); // bluetooth stack will go into congestion, if too many packets are sent, in 6 hours test i was able to go as low as 3ms
    }

    if (!deviceConnected) {
        Serial.println("No device connected!");
    }

    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }

    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }

//    auto color = list;
//    auto r = (String) color.begin()[0];
//    auto g = (String) color.begin()[1];
//    auto b = (String) color.begin()[2];
//    auto c = (String) color.begin()[3];
//    auto temp = (String) color.begin()[4];
//    auto lux = (String) color.begin()[5];
//
//    String a = "R: " + r + ", G: " + g + ", B: " + b + ", C: " + c + ", TEMP: " + temp + ", LUX: " + lux;
//    uint8_t buf[a.length()];
//    memcpy(buf, a.c_str(), a.length());
//    SerialBT.write(buf, a.length());
//    SerialBT.println();
//
//    if (SerialBT.connected()) {
//        if (Serial.available()) {
//            SerialBT.write(Serial.read());
//        }
//
//        if (SerialBT.available()) {
//            Serial.write(SerialBT.read());
//        }
//    }
}

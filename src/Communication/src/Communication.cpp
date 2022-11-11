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

// Make sure Hardware Serial can be used in the file
extern HardwareSerial Serial;

// Define our *static* UUIDs to start our Bluetooth instance
#define SERVICE_UUID        "d6960225-2fbc-4565-bf52-0f1cc61bbfcf"
#define CHARACTERISTIC_UUID "13d258f5-80c4-4863-a995-53604358e2e5"

// Declare our Bluetooth server and Characteristics
BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristic = NULL;

// Declare variables so we can check or bluetooth connection status
bool deviceConnected;
bool oldDeviceConnected;
uint32_t value = 0;

/**
 * Define our Bluetooth callback.
 */
class MyServerCallbacks : public BLEServerCallbacks {
    /**
     * Run this function when a new device connected to our ESP
     * @param pServer
     */
    void onConnect(BLEServer *pServer) {
        deviceConnected = true;
        Serial.println("New connection established");
    };

    /**
     * Run this function when a device disconnected from our ESP
     * @param pServer
     */
    void onDisconnect(BLEServer *pServer) {
        deviceConnected = false;
        Serial.println("Dropped current connection..");
    }
};

/**
 * Define our startup sequence for a bluetooth connection
 * This needs to be run in setup()
 */
void Communication::setBT() {
    // Reset our bluetooth properties when we run the setup on a restart
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

    // Create a BLE Descriptor
    pCharacteristic->addDescriptor(new BLE2902());

    // Start the Bluetooth service
    pService->start();

    // Start advertising our service
    pServer->getAdvertising()->start();

//    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
//    pAdvertising->addServiceUUID(SERVICE_UUID);
//    pAdvertising->setScanResponse(false);
//    pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
//    BLEDevice::startAdvertising();
}

/**
 * Send values to our connected device, over Bluetooth
 * This function needs to be run in loop()
 * @param list
 */
void Communication::writeBT(int *list) {
    // Store String versions of the ints in the passed array in new variables
    String r = (String) list[0];
    String g = (String) list[1];
    String b = (String) list[2];
    String c = (String) list[3];
    String temp = (String) list[4];
    String lux = (String) list[5];

    // Prepare and send a value
    uint8_t val[3] = {255, 0, 0};
    pCharacteristic->setValue((uint8_t *) &val, 3);
    pCharacteristic->notify();

    // Prepare and send a value
    uint8_t val1[5] = {'R', 'U', 'B', 'E', 'N'};
    pCharacteristic->setValue((uint8_t *) &val1, 5);
    pCharacteristic->notify();

    // While disconnected
    if (!deviceConnected) {
        Serial.println("No device connected!");
    }

    // While connected
    if (deviceConnected) {
        Serial.println("Device connected!");

        // Bug: (prepared) messages won't send from inside an if statement(?)

        delay(3); // bluetooth stack will go into congestion, if too many packets are sent, in 6 hours test i was able to go as low as 3ms
    }

    // Disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("Restarting advertising..");
        oldDeviceConnected = deviceConnected; // Set oldDeviceConnected to false
    }

    // Connecting
    if (deviceConnected && !oldDeviceConnected) {
        Serial.println("Connecting to a new device..");
        oldDeviceConnected = deviceConnected; // If we connect to a device, set oldDeviceConnected to true
    }
}

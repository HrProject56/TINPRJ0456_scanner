// //
// // Created by rwfli on 08/11/2022.
// //

// #include <Arduino.h>
// #include <iostream>
// #include "Communication.hpp"
// #include <BLEDevice.h>
// #include <BLEUtils.h>
// #include <BLEServer.h>
// #include <BLE2902.h>
// //#include "../../../lib/BluetoothSerial/src/BluetoothSerial.h"

// // Make sure Hardware Serial can be used in the file
// extern HardwareSerial Serial;

// // Define our *static* UUIDs to start our Bluetooth instance
// #define SERVICE_UUID                "d6960225-2fbc-4565-bf52-0f1cc61bbfcf"
// #define CHARACTERISTIC_UUID         "13d258f5-80c4-4863-a995-53604358e2e5"
// #define CHARACTERISTIC_UUID_RX      "2df0194c-8eca-4633-9cf1-dbae41267a5b"

// // Declare our Bluetooth server and Characteristics
// BLEServer *pServer = NULL;
// BLECharacteristic *pCharacteristic = NULL;

// // Declare variables so we can check or bluetooth connection status
// bool deviceConnected;
// bool oldDeviceConnected;
// uint32_t value = 0;

// /**
//  * Define our Bluetooth callback.
//  */
// class MyServerCallbacks : public BLEServerCallbacks {
//     /**
//      * Run this function when a new device connected to our ESP
//      * @param pServer
//      */
//     void onConnect(BLEServer *pServer) {
//         deviceConnected = true;
//         Serial.println("New connection established");
//     };

//     /**
//      * Run this function when a device disconnected from our ESP
//      * @param pServer
//      */
//     void onDisconnect(BLEServer *pServer) {
//         deviceConnected = false;
//         Serial.println("Dropped current connection..");
//     }
// };

// class MyCallbacks : public BLECharacteristicCallbacks {
//     void onWrite(BLECharacteristic *pCharacteristic) {
//         std::string rxValue = pCharacteristic->getValue();

//         if (rxValue.length() > 0) {
//             Serial.println("*********");
//             Serial.print("Received Value: ");
//             for (int i = 0; i < rxValue.length(); i++)
//                 Serial.print(rxValue[i]);

//             Serial.println();
//             Serial.println("*********");
//         }
//     }
// };

// /**
//  * Define our startup sequence for a bluetooth connection
//  * This needs to be run in setup()
//  */
// void Communication::setBT() {
//     // Reset our bluetooth properties when we run the setup on a restart
//     deviceConnected = false;
//     oldDeviceConnected = false;
//     value = 0;

//     // Create the BLE Device
//     BLEDevice::init("ColorSensor");

//     // Create the BLE Server
//     pServer = BLEDevice::createServer();
//     pServer->setCallbacks(new MyServerCallbacks());

//     // Create the BLE Service
//     BLEService *pService = pServer->createService(SERVICE_UUID);

//     // Create a BLE Characteristic
//     pCharacteristic = pService->createCharacteristic(
//             CHARACTERISTIC_UUID,
//             BLECharacteristic::PROPERTY_READ |
//             BLECharacteristic::PROPERTY_WRITE |
//             BLECharacteristic::PROPERTY_NOTIFY |
//             BLECharacteristic::PROPERTY_INDICATE
//     );

//     // Create a BLE Descriptor
//     pCharacteristic->addDescriptor(new BLE2902());

//     BLECharacteristic *pRxCharacteristic = pService->createCharacteristic(
//             CHARACTERISTIC_UUID_RX,
//             BLECharacteristic::PROPERTY_WRITE
//     );

//     pRxCharacteristic->setCallbacks(new MyCallbacks());

//     // Start the Bluetooth service
//     pService->start();

//     // Start advertising our service
//     pServer->getAdvertising()->start();

// //    // iPhone optimization
// //    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
// //    pAdvertising->addServiceUUID(SERVICE_UUID);
// //    pAdvertising->setScanResponse(false);
// //    pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
// //    BLEDevice::startAdvertising();
// }

// /**
//  * Send values to our connected device, over Bluetooth
//  * This function needs to be run in loop()
//  * @param list
//  */
// void Communication::writeBT(unsigned short *list) {
//     try {
//         // map all items to 8 bit
//         for (int i = 1; i < 4; i++) {
//             list[i] = map(list[i], 0, 1023, 0, 255);
//         }

//         // Prepare and push package to phone
//         uint8_t val[3] = {(uint8_t) list[1], (uint8_t) list[2], (uint8_t) list[3]};
//         pCharacteristic->setValue((uint8_t *) &val, 3);
//         pCharacteristic->notify();

//         // Connecting
//         if (deviceConnected && !oldDeviceConnected) {
//             Serial.println("Connecting to a new device..");
//             oldDeviceConnected = deviceConnected; // If we connect to a device, set oldDeviceConnected to true
//         }

//         // Disconnecting
//         if (!deviceConnected && oldDeviceConnected) {
//             delay(500); // give the bluetooth stack the chance to get things ready
//             pServer->startAdvertising(); // restart advertising
//             Serial.println("Restarting advertising..");
//             oldDeviceConnected = deviceConnected; // Set oldDeviceConnected to false
//             delay(500); // give the bluetooth stack the chance to get things ready
//         }

//         // While disconnected
//         if (!deviceConnected) {
//             Serial.println("No device connected!");
//             delay(3);
//         }

//         // While connected
//         if (deviceConnected) {
//             Serial.println("Device connected!");

//             /**
//              * Bug: (prepared) messages won't send from inside an if statement(?)
//              * Prepare and send a value
//              * uint8_t val1[5] = {'R', 'U', 'B', 'E', 'N'};
//              * pCharacteristic->setValue((uint8_t *) &val1, 5);
//              * pCharacteristic->notify();
//              */

//             delay(3); // bluetooth stack will go into congestion, if too many packets are sent, in a 6 hours test I was able to go as low as 3ms
//         }
//     } catch (std::exception &e) {
//         std::cout << " a standard exception was caught, with message '" << e.what() << "'\n";
//     }
// }
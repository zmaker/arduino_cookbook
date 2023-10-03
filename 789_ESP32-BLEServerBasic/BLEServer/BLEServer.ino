#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

void setup() {
  Serial.begin(115200);
  Serial.println("BLE Server - fix");


  BLEDevice::init("ESP322BLE - Server");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
  pCharacteristic->setValue("Hello BLE ESP32!!!!!");
  pService->start();

  BLEAdvertising *padv = BLEDevice::getAdvertising();
  padv->addServiceUUID(SERVICE_UUID);
  padv->setScanResponse(true);
  padv->setMinPreferred(0x06);
  padv->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
}

void loop() {
  // put your main code here, to run repeatedly:

}

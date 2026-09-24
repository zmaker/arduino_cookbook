//https://github.com/DFRobot/DFRobot_OzoneSensor
#include "DFRobot_OzoneSensor.h"

#define COLLECT_NUMBER   20              // campioni per la media (1-100)
#define Ozone_IICAddress OZONE_ADDRESS_3 // 0x73: controlla i DIP switch

DFRobot_OzoneSensor Ozone;

void setup() {
  Serial.begin(9600);
  while (!Ozone.begin(Ozone_IICAddress)) {
    Serial.println("Sensore non trovato su I2C!");
    delay(1000);
  }
  Serial.println("Sensore OK");
  // PASSIVE: legge solo quando lo chiedi tu; AUTOMATIC: misura in continuo
  Ozone.setModes(MEASURE_MODE_PASSIVE);
}

void loop() {
  int16_t ozono = Ozone.readOzoneData(COLLECT_NUMBER);
  Serial.print("Ozono: ");
  Serial.print(ozono);
  Serial.println(" ppb");
  delay(1000);
}
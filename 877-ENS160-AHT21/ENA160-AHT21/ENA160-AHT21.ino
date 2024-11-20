/***************************************************************************
  ENS160 - Digital Air Quality Sensor

  AQI - air quality index - 0 - 500 (0 = OTTIMO 500 = PESSIMO)
  TVOC - Composti organici volatili totali, o TVOC (ppb parti per billion 0 - 1000 alto = PESSIMO)
  eCO2 - L'eCO₂ viene calcolato attraverso un algoritmo che utilizza i livelli di VOC (TVOC) 
          per fare una stima della CO₂ presente nell'ambiente. Anche se non rappresenta la concentrazione reale 
          di CO₂, offre un'indicazione utile per valutare la qualità dell'aria
          ( DA 0 A 5000 ) ppm
  
 ***************************************************************************/
#include <Wire.h>
#include "ScioSense_ENS160.h"
ScioSense_ENS160 ens160(ENS160_I2CADDR_1); 

#include <Adafruit_AHTX0.h>
Adafruit_AHTX0 aht;

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  ens160.begin();
  if (ens160.available()) {
    ens160.setMode(ENS160_OPMODE_STD);
  }

  if (!aht.begin()) {
    Serial.println("errore aht");
    while (1);
  }
}

void loop() {
  if (ens160.available()) {
    ens160.measure(true);
    float aqi = ens160.getAQI();
    float tvoc = ens160.getTVOC();
    float eco2 = ens160.geteCO2();

    sensors_event_t hum, temp;
    aht.getEvent(&hum, &temp);
    float t1 = temp.temperature;
    float h1 = hum.relative_humidity;

    Serial.print("AQI: ");Serial.print(aqi);Serial.print("\t ");
    Serial.print("TVOC: ");Serial.print(tvoc);Serial.print(" ppb\t ");
    Serial.print("CO2: ");Serial.print(eco2);Serial.print(" ppm\t");
    Serial.print("t: ");Serial.print(t1);Serial.print(" C\t");
    Serial.print("h: ");Serial.print(h1);Serial.print(" %\n");
  }
  delay(2000);
}

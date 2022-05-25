/**
 * Localizzatore con SIM800 e GPS NEO6
 */
#include <SoftwareSerial.h>
#include "TinyGPS.h"

#include "parametri.h"
#include "stati.h"

SoftwareSerial sim800(PIN_GSM_TX, PIN_GSM_RX);
SoftwareSerial neo6(PIN_GPS_TX, PIN_GPS_RX);
TinyGPS gps;

void setup() {
  Serial.begin(9600);
  
  //attendo l'avvio del modulo sim800
  for (int i = 0; i < 5; i++) {
    delay(1000);
    Serial.print(".");
  }
  Serial.print("o");
  sim800.begin(9600);
  Serial.print("O");
  neo6.begin(9600);
  Serial.println("X");  
}

void loop() {
  switch (stato) {
    case startup:
      act_startup(&Serial);
      break;
    case work:
      act_work(&Serial);
      break;
    case getposition:
      act_getposition(&Serial, &neo6, &gps);
      break;
    case callservice:
      act_callservice(&Serial);
      break;
  }
}

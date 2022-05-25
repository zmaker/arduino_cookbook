/**
 * Localizzatore con SIM800 e GPS NEO6
 * 
 * info: https://lastminuteengineers.com/sim800l-gsm-module-arduino-tutorial/
 */
#include <SoftwareSerial.h>
#include "TinyGPS.h"

#include "parametri.h"
#include "stati.h"

SoftwareSerial sim800(PIN_GSM_RX, PIN_GSM_TX);
SoftwareSerial neo6(PIN_GPS_TX, PIN_GPS_RX);
TinyGPS gps;

void setup() {
  Serial.begin(9600);
  //reset del modulo
  pinMode(PIN_GSM_RST, OUTPUT);
  Serial.print("R");
  digitalWrite(PIN_GSM_RST, HIGH);
  delay(200);
  digitalWrite(PIN_GSM_RST, LOW);
  
  //attendo l'avvio del modulo sim800
  for (int i = 0; i < 6; i++) {
    delay(2000);
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
      act_startup(&Serial, &sim800);
      break;
    case work:
      act_work(&Serial);
      break;
    case getposition:
      act_getposition(&Serial, &neo6, &gps);
      break;
    case callservice:
      act_callservice(&Serial, &sim800);
      break;
    case terminal:
      act_terminal(&Serial, &sim800);
      break;
  }
}

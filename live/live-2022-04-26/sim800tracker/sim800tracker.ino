#include <SoftwareSerial.h>
#include "TinyGPS.h"

#include "parametri.h"
#include "stati.h"

SoftwareSerial sim800(PIN_GSM_TX, PIN_GSM_RX);
SoftwareSerial neo6(PIN_GPS_TX, PIN_GPS_RX);
TinyGPS gps;

void setup() {
  Serial.begin(9600);
  
  for (int i = 0; i < 6; i++) {
    delay(500); 
    Serial.print("."); 
  }
  Serial.print("o");
  sim800.begin(9600);
  Serial.print("O");
  neo6.begin(9600);
  Serial.println("X");
  
  sim800.listen();
}

void loop() {
  switch (stato) {
    case startup:
      act_startup();
      break;
    case work:
      act_work();
      break;
    case getposition:
      act_getposition();
      break;
    case callservice:
      act_callservice();
      break;
  }
}

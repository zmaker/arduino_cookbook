#include <Arduino.h>
#include "SPIFFS.h"

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("SPIFFS test - Platformio");

  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS ERROR: HALT");
    while(1);
  }

  File file = SPIFFS.open("/test.txt");
  if (!file) {
    Serial.println("SPIFFS ERROR: File non trovato");
  } else {
    while (file.available()) {
      Serial.write(file.read());
    }
    file.close();
  }

  //creo file 
  file = SPIFFS.open("/log.txt", FILE_APPEND); //FILE_WRITE
  if (!file) {
    Serial.println("SPIFFS ERROR: File non trovato");
  } else {
    file.println("ABCDEF");      
    file.close();
  }

  Serial.println("\n");

  file = SPIFFS.open("/log.txt");
  if (!file) {
    Serial.println("SPIFFS ERROR: File non trovato");
  } else {
    while (file.available()) {
      Serial.write(file.read());
    }
    file.close();
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
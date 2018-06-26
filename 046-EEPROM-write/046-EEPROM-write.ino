/**
 Cookbook #46 - EEPROM - 
 scrive all'indirizzo 0 un valore numerico
 */

#include <EEPROM.h>

void setup() {
  Serial.begin(9600);
  
  int valore = 100;
  EEPROM.write(0, valore);

  char msg[5] = "hello";
  EEPROM.put(2, msg);

  Serial.println("valori scritti nella EEPROM");
}

void loop() {  
}

/**
 Cookbook #46 - EEPROM - 
 legge i valori scritti
 */

#include <EEPROM.h>

void setup() {
  Serial.begin(9600);

  int valore = EEPROM.read(0);

  Serial.print("valore trovato nella EEPROM interna: ");
  Serial.println(valore);

  char msg[5];
  EEPROM.get(2, msg);

  Serial.print("messaggio trovato nella EEPROM interna: ");
  Serial.println(msg);
}

void loop() {  
}

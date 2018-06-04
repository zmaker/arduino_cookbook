#include <CapacitiveSensor.h>
 
//La libreria fornisce un oggetto da inizializzare con i pin digitali da usare
//il sensore va collegato sul pin 11
// tra 10 e 11 c'è una resistenza da 10Mohm
CapacitiveSensor touch = CapacitiveSensor(10,11);
 
void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  //disattiva l'autocalibrazione del sensore ???????
  //touch.set_CS_AutocaL_Millis(0xFFFFFFFF);
}
 
void loop() {
  //leggo il valore registrato dal sensore e specifico di fare 30 campionamenti
  long value =  touch.capacitiveSensor(30);
  Serial.println(value);
  if (value > 500) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
  delay(10);
}

#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  delay(1000);
  Serial.println("ok");
  
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), letturaingressi, FALLING);
}

volatile int st = LOW; //volatile non può essere cambiata da altre parti di codice

void loop() {
  if (st) {
    Wire.requestFrom(0x38,1);
    if (Wire.available()) {
      byte b = Wire.read();
      Serial.println(b, BIN); 
      st = LOW;  
    }
       
  }
  
}

/*
 * Funzione di gestione dell'interrupt: non riceve parametri e non 
 * restituisce nulla.
 * Deve essere rapida e può usare solo variabili volatili e globali
 */
void letturaingressi() {
  st = HIGH;  
}

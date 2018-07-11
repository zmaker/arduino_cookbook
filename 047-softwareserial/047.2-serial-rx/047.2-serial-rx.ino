/*
 * 047 - Arduino cookbook
 * 
 * sketch da caricare sul secondo arduino che fa da ricevitore 
 * dati sulla seriale software ai pin 10 e 11
 * 
 * Incrociate i collegamenti! tx su rx e rx su tx
 * 
 */

#include <SoftwareSerial.h>

#define SOFTRX 10
#define SOFTTX 11

SoftwareSerial SerialS(SOFTRX, SOFTTX);

void setup() {  
  pinMode(SOFTTX, OUTPUT);
  pinMode(SOFTRX, INPUT);

  delay(3000);
  
  Serial.begin(9600);
  Serial.println("Pronto a ricevere da arduino 1");
  
  SerialS.begin(9600);
}

void loop() {
  if (SerialS.available()){
    //ricevo un carattere dalla seriale software
    //lo scrivo sulla seriale vera, collegata al pc
    Serial.write(SerialS.read());
  }
}

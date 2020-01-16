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

  pinMode(13, OUTPUT);

  delay(3000);
  
  Serial.begin(9600);
  Serial.println("Pronto a ricevere da arduino 1");
  
  SerialS.begin(9600);
}

void loop() {
  if (SerialS.available()){
    char ch = SerialS.read();
    //ricevo un carattere dalla seriale software
    //lo scrivo sulla seriale vera, collegata al pc
    Serial.write(ch);
    switch (ch) {
      case '0':
        blink(0);
      break;
      case '1':
        blink(1);
      break;
      case '2':
        blink(2);
      break;
      case '3':
        blink(3);
      break;  
    }
  }
}

void blink (int n) {
  for (int i = 0; i < n+1; i++){
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);  
  }  
}

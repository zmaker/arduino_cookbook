#include <SoftwareSerial.h>

#define SSerialRX        10 
#define SSerialTX        11 
#define SSerialTxControl 3  
#define RS485Transmit    HIGH
#define RS485Receive     LOW

#define Pin13LED         13

SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

void setup(){
  Serial.begin(9600);
  pinMode(SSerialTxControl, OUTPUT);
  digitalWrite(SSerialTxControl, RS485Receive); 
  RS485Serial.begin(4800);  
}

byte stato = 0;

void loop(){
    digitalWrite(SSerialTxControl, RS485Transmit); 
    int n = (stato%3);
    //Serial.println(n);
    RS485Serial.write( n );  //produce una sequenza: 0, 1, 2 
    delay(10);
    digitalWrite(SSerialTxControl, RS485Receive);  // Disable RS485 Transmit       
    stato++;

    //si mette in ascolto
    if (RS485Serial.available()) {
      byte data = RS485Serial.read();
      Serial.println(data, DEC); 
   }
   delay(1000);
}

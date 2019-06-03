#include <SoftwareSerial.h>
#define SSerialRX        10  //Serial Receive pin
#define SSerialTX        11  //Serial Transmit pin

#define SSerialTxControl 3   //RS485 Direction control

#define RS485Transmit    HIGH
#define RS485Receive     LOW

#define Pin13LED         13

SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

void setup() {
  Serial.begin(9600);

  pinMode(Pin13LED, OUTPUT);
  pinMode(SSerialTxControl, OUTPUT);

  digitalWrite(SSerialTxControl, RS485Receive);  // Init Transceiver   

  RS485Serial.begin(4800); 

}

void loop() {
  
  if (RS485Serial.available()) {
    byte n = RS485Serial.read();
    if (n == 0) {
      digitalWrite(Pin13LED, HIGH);
      delay(500);
      digitalWrite(Pin13LED, LOW);
    }
    delay(10); 
   }

}

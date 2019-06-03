#include <SoftwareSerial.h>
#define SSerialRX        10  //Serial Receive pin
#define SSerialTX        11  //Serial Transmit pin

#define SSerialTxControl 3   //RS485 Direction control

#define RS485Transmit    HIGH
#define RS485Receive     LOW

#define Pin13LED         13

SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

int byteReceived;
int byteSend;

void setup() {
  Serial.begin(9600);

  pinMode(Pin13LED, OUTPUT);
  pinMode(SSerialTxControl, OUTPUT);

  digitalWrite(SSerialTxControl, RS485Receive);  // Init Transceiver   

  RS485Serial.begin(4800); 

}

void loop() {
  
  if (RS485Serial.available())  //Look for data from other Arduino
   {
    byteReceived = RS485Serial.read();    // Read received byte
    delay(10);
    digitalWrite(Pin13LED, byteReceived);  // Show activity   
   }

}

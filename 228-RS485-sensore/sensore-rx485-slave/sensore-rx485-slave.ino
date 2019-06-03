#include <SoftwareSerial.h>
#include <SimpleDHT.h>

#define SSerialRX        10
#define SSerialTX        11
#define SSerialTxControl 3 
#define RS485Transmit    HIGH
#define RS485Receive     LOW

SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX

SimpleDHT11 dht11;

void setup() {
  Serial.begin(9600);
  pinMode(SSerialTxControl, OUTPUT);
  digitalWrite(SSerialTxControl, RS485Receive);  // Init Transceiver   
  RS485Serial.begin(4800); 
}

void loop() {  
  if (RS485Serial.available()) {
    byte n = RS485Serial.read();
    if (n == 0) {
      Serial.println("req");
      readSensor();
    }
    delay(10); 
   }

}

void readSensor(){
  byte temp = 0;
  byte umid = 0;

  int err = SimpleDHTErrSuccess;
  dht11.read(2, &temp, &umid, NULL);

  digitalWrite(SSerialTxControl, RS485Transmit); 
  RS485Serial.write( temp );
  RS485Serial.write( umid ); 
  delay(10);
  digitalWrite(SSerialTxControl, RS485Receive);
  
  Serial.print((int)temp); Serial.print(" C, "); 
  Serial.print((int)umid); Serial.println(" H");
}

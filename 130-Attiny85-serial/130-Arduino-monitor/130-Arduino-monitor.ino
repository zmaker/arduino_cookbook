#include <SoftwareSerial.h>

#define RX    9   // *** D3, Pin 2
#define TX    10   // *** D4, Pin 3

SoftwareSerial SSerial(RX, TX);

void setup() {
  SSerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if (SSerial.available()) {
    char ch = SSerial.read();
    Serial.write(ch);  
  }
}

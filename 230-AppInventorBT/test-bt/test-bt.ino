#include <SoftwareSerial.h>

SoftwareSerial SSerial(6, 7); //6 RX e 7 TX

void setup() {
  Serial.begin(38400);
  while(!Serial) {}

  Serial.println("ok");
  SSerial.begin(38400);
}

void loop() {
  if (SSerial.available()){
    Serial.write(SSerial.read());
  }
  if (Serial.available()){
    SSerial.write(Serial.read());
  }
}


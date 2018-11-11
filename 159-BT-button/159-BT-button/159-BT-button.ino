#include <SoftwareSerial.h>

SoftwareSerial SSerial(6, 7); //6 RX e 7 TX

void setup() {
  Serial.begin(9600);
  while(!Serial) {}

  Serial.println("ok");
  SSerial.begin(115200);

  pinMode(2, INPUT);
}

void loop() {
  if (digitalRead(2)) {
    Serial.println("BT");
    SSerial.println("pressed!");
  }  
}

#include <SoftwareSerial.h>

SoftwareSerial port(10, 11); // RX, TX

void setup() {
  port.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  if (port.available()) {
    int n = port.read();
    digitalWrite(2, bitRead(n, 0));
    digitalWrite(3, bitRead(n, 1));
  }
}

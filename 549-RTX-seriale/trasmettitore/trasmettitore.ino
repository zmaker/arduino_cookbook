#include <SoftwareSerial.h>

SoftwareSerial port(10, 11); // RX, TX

void setup() {
  port.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
}


int buf;

void loop() {
  buf = 0;
  if (digitalRead(2)) bitSet(buf, 0);
  if (digitalRead(3)) bitSet(buf, 1);
    
  port.write(buf);
}

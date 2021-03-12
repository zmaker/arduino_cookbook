/*
https://learn.sparkfun.com/tutorials/openlog-hookup-guide/all
*/
#include <SoftwareSerial.h>
SoftwareSerial openlog = SoftwareSerial(3, 2); //RX, TX

void setup() {
  openlog.begin(9600);
  pinMode(13, OUTPUT);
}

int c = 0;

void loop() {
  digitalWrite(13, HIGH);
  openlog.print("count: ");
  openlog.println(c);
  c++;
  delay(100);
  digitalWrite(13, LOW);
  delay(5000);
}

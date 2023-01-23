#include <SoftwareSerial.h>

SoftwareSerial ss(3, 2); //3-RX, 2-TX

void setup() {
  Serial.begin(9600);
  ss.begin(9600);
  delay(1000);
  Serial.println("CF");

}

void loop() {
  if (ss.available()) {
    Serial.write(ss.read());
  }
  delay(1);
}

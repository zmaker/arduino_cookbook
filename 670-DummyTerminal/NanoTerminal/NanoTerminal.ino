#include <SoftwareSerial.h>
SoftwareSerial modem(3, 2); //RX, TX

void setup() {
  Serial.begin(9600);
  modem.begin(9600);
}

void loop() {
  if (Serial.available())  {
    modem.write(Serial.read());
  }
  if (modem.available())  {
    Serial.write(modem.read());
  }
}

#include <SoftwareSerial.h>
/*
per leggere l'ora dalla rete
AT+CCLK?

La prima volta:
at+clts=1
at&W

*/

SoftwareSerial modem(6, 7); //RX, TX

void setup() {
  Serial.begin(9600);
  modem.begin(9600);
  delay(100);
  pinMode(9, OUTPUT);

  digitalWrite(9, LOW);
  delay(100);
  digitalWrite(9, HIGH);
  delay(100);
  digitalWrite(9, LOW);
  delay(100);

  Serial.println("SIM800: ");

}

void loop() {
  if (modem.available()) {
     char c = modem.read();
     Serial.write(c);
  }
  if (Serial.available()) {
     char c = Serial.read();
     modem.write(c);
  }
}

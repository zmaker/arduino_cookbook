#include <SoftwareSerial.h>

#define SER_TX 2
#define SER_RX 3

SoftwareSerial modem(SER_RX, SER_TX);

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 5; i++) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\n");
  modem.begin(9600);
  Serial.println("SIM808: ready");
}

void loop() {
  if (modem.available()) {
    char ch = modem.read();
    Serial.write(ch);  
  }
  if (Serial.available()) {
    char ch = Serial.read();
    modem.write(ch);  
  }
}

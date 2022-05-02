#include <SoftwareSerial.h>

#define SER_RX 3
#define SER_TX 2
SoftwareSerial modem(SER_RX, SER_TX);

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 6; i++) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nSIM868: ");
  modem.begin(9600);
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

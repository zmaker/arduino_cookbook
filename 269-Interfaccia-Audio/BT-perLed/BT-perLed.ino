#include <SoftwareSerial.h>

SoftwareSerial SSerial(6, 7);  //6 RX 7 TX

void setup() {
  Serial.begin(9600);
  SSerial.begin(9600);
  Serial.println("ok");

  pinMode(13, HIGH);
}

void loop() {
  if (SSerial.available()) {
    char ch = SSerial.read();
    Serial.println(ch);
    if (ch == 'a') {
      digitalWrite(13, HIGH);
      Serial.println("ON");
    }
    if (ch == 's') {
      digitalWrite(13, LOW);
      Serial.println("OFF");
    }
      
  }
}

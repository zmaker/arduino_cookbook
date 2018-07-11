#include <SoftwareSerial.h>

SoftwareSerial SSerial(6, 7); //6 RX e 7 TX

void setup() {
  Serial.begin(9600);
  while(!Serial) {}

  Serial.println("ok");
  SSerial.begin(9600);

  pinMode(13, OUTPUT);
}

void loop() {
  if (SSerial.available()){
    char ch = SSerial.read();
    Serial.write(ch);
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

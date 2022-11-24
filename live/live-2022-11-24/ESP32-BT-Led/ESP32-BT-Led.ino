#include "BluetoothSerial.h"

BluetoothSerial bt;
String line;

void setup() {
  pinMode(2, OUTPUT);

  Serial.begin(115200);  
  delay(1000);
  Serial.println("ESP32 BT LED");

  bt.begin("ESP32-BT1");
}

void loop() {
  if (bt.available()) {
    char ch = bt.read();
    if (ch == '\n') {      
      //ho la linea
      Serial.println(line);
      //elaboro la linea
      if (line == "on") {
        Serial.println("accendo il led");
        digitalWrite(2, HIGH);
      } else if (line == "off") {
        Serial.println("spengo il led");
        digitalWrite(2, LOW);
      }
      //la svuoto
      line = "";
    } else if (ch != '\r') {
      line += ch;
    }
  }
}

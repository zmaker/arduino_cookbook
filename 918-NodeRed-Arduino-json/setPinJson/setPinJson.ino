/*
{"pin":11}
{"pin":11, "value":1}
{"pin":11, "value":0}

*/
#include <ArduinoJson.h>
const size_t JSON_BUFFER_SIZE = 128;

String linea = "";

void setup() {
  Serial.begin(9600);
  while (!Serial) {}
}

void loop() {
  while (Serial.available()){
    char ch = (char)Serial.read();
    if (ch == '\n'){
      processInput(linea);
      linea = "";
      pinMode(13, OUTPUT);
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
    } else {
      linea += ch;
    }
  }

}

void processInput(const String &str){
  StaticJsonDocument<JSON_BUFFER_SIZE> doc;
  DeserializationError error = deserializeJson(doc, str);

  if (error) {
    Serial.println("{'error':'errore json'}");
    return;
  }

  if (!doc.containsKey("pin")) {
    Serial.println("{'error':'errore json - manca pin'}");
    return;
  }

  int pin = doc["pin"];
  if (doc.containsKey("value")) {
    int value = doc["value"];
    pinMode(pin, OUTPUT);
    digitalWrite(pin, value);
    serializeJson(doc, Serial);
    Serial.println();
  } else {
    int val = digitalRead(pin);
    StaticJsonDocument<JSON_BUFFER_SIZE> res;
    res["pin"] = pin;
    res["value"] = val;
    serializeJson(res, Serial);
    Serial.println();
  }
}

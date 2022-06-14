#include <ArduinoJson.h>

void setup() {
  Serial.begin(9600);
  while (!Serial) continue;

  DynamicJsonDocument doc(1024);
  doc["nome"] = "Paolo";
  doc["cap"] = 20020;
  doc["corsi"][0] = "math";
  doc["corsi"][1] = "cad";
  doc["corsi"][2] = "eng";
  doc["posizione"]["lat"] = 45.34567;
  doc["posizione"]["lon"] = 9.25346;
  serializeJson(doc, Serial);
  //https://jsonformatter.curiousconcept.com/#
}

void loop() {
  // put your main code here, to run repeatedly:

}

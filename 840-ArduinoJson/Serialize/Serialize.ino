#include <ArduinoJson.h>

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(1);
  Serial.println("serialize json");

  //https://arduinojson.org/v6/assistan
  StaticJsonDocument<200> doc;

  /*
  {
    "nome":"Mario", "cognome":"Rossi", "uid":123, "hobby":["arduino", "pizza"]
  }
  */

  doc["nome"] = "Mario";
  doc["cognome"] = "Rossi";
  doc["uid"] = 123;

  JsonArray lista = doc.createNestedArray("hobby");
  lista.add("arduino");
  lista.add("pizza");
  
  JsonObject obj = doc.createNestedObject("addr");
  obj["citta"] = "Milano";
  obj["via"] = "via Roma, 12";

  serializeJson(doc, Serial);
  Serial.println();

  serializeJsonPretty(doc, Serial);
  Serial.println();

}

void loop() {
  // put your main code here, to run repeatedly:

}

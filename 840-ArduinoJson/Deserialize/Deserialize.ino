#include <ArduinoJson.h>

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(1);
  Serial.println("de-serialize json");

  //https://arduinojson.org/v6/assistan
  StaticJsonDocument<200> doc;

  char json[] = "{\"nome\":\"Mario\",\"cognome\":\"Rossi\",\"uid\":123,\"hobby\":[\"arduino\",\"pizza\"]}";

  DeserializationError err = deserializeJson(doc, json);
  if (err) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(err.f_str());
    while(1);
  }

  const char* nome = doc["nome"];
  const char* cognome = doc["cognome"];
  int uid = doc["uid"];//.as<int>();

  const char* el1 = doc["hobby"][0];
  const char* el2 = doc["hobby"][1];

  Serial.println(nome);
  Serial.println(cognome);
  Serial.println(uid);
  Serial.println(el1);
  Serial.println(el2);
}

void loop() {
  // put your main code here, to run repeatedly:

}

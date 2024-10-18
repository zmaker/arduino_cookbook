#include <SD.h>
#include <ArduinoJson.h>

#define CS_PIN 10

void setup() {
  Serial.begin(9600);
  if (!SD.begin(CS_PIN)){
    Serial.println("initialization failed. ");
    while (true);
  }

  Serial.println("write json");
  //creo una struttura dati con json
  StaticJsonDocument<200> doc;
  doc["msg"] = "Hello world";
  doc["pin"] = 6;
  doc["blink"] = 500;
  //la stampo su serial monitor
  serializeJson(doc, Serial);
  Serial.println(" ");

  //se il file esiste lo cancello
  if (SD.exists("/conf.jsn")) {
    Serial.println("file esiste: lo cancello");
    SD.remove("/conf.jsn");
  }

  //scrivo il file
  File f = SD.open("/conf.jsn", FILE_WRITE);
  if (f) {
    if (serializeJson(doc, f) == 0) {
      Serial.println("json errore");
    } else {
      Serial.println("json scritto");
    }
    f.close();
  } else {
    Serial.println("errore file");
  }
}

void loop() {}



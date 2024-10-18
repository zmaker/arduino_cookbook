#include <SD.h>
#include <ArduinoJson.h>

#define CS_PIN 10

int blink = 1000;

void setup() {
  Serial.begin(9600);
  if (!SD.begin(CS_PIN)){
    Serial.println("initialization failed. ");
    while (true);
  }

  Serial.println("read json");
  //apro il file
  File f = SD.open("/conf.jsn");
  if (f) {
    //creo un doc json
    StaticJsonDocument<200> doc;
    // provo a leggere il file
    DeserializationError err = deserializeJson(doc, f);
    f.close();

    if (err) {
      Serial.println(err.c_str());
      while(true);
    }

    //interpreto i dati
    const char* msg = doc["msg"];
    int pin = doc["pin"];
    blink = doc["blink"];

    Serial.print("Msg: ");
    Serial.println(msg);
    Serial.print("pin: ");
    Serial.println(pin);
    Serial.print("blink: ");
    Serial.println(blink);

  }

}

void loop() {
  Serial.println("X");
  delay(blink);
}

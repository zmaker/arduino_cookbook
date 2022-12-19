// https://github.com/me-no-dev/ESPAsyncWebServer
// https://github.com/me-no-dev/ESPAsyncTCP

#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

const char* ssid = "...";
const char* password = "...";

AsyncWebServer server(80);

String processor(const String& var);

void setup() {
  Serial.begin(115200);
  delay(3000);
  pinMode(4, OUTPUT);

  if (!SPIFFS.begin(true)) {
    Serial.println("err SPIFFS");
    while (1);
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");  
  }
  Serial.print("IP: ");Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("call index");  
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(4, HIGH);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(4, LOW);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  server.begin();
}

void loop() {  
}

String processor(const String& var){
  //STATO_LED
  Serial.println(var);  
  if (var == "STATO_LED") {
    String ledstate = "";
    if (digitalRead(4)) {
      ledstate = "ON";
    } else {
      ledstate = "OFF";
    }
    return ledstate;
  }
  return String();
}

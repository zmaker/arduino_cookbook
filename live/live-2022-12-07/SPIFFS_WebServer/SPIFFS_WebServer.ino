#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"
#include <WiFi.h>
/**
 * https://github.com/me-no-dev/ESPAsyncWebServer
 * https://github.com/me-no-dev/AsyncTCP
 * 
 */

const char* ssid = "www.reelco.it";
const char* password = "pass";
 
AsyncWebServer server(80);

String processor(const String& par);

void setup() {
  Serial.begin(115200);
  if (!SPIFFS.begin(true)){
    Serial.println("SPIFFS ERROR");
    while(1);
  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *req){
    req->send(SPIFFS, "/index.html", String(), false, processor);
  });

  server.on("/home.html", HTTP_GET, [](AsyncWebServerRequest *req){
    req->send(SPIFFS, "/home.html", String(), false, processor);
  });

  server.begin();
}

void loop() {
}

String processor(const String& par){
  return String();
}

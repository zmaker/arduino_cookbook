#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

ESP8266WebServer server(80);

void setup(void) {
  Serial.begin(115200);
  Serial.println("setup");
  
  WiFi.mode(WIFI_STA);
  WiFi.begin("wifi", "password");
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", helloworld);
  
  server.begin();  
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}

void helloworld() {  
  Serial.println("request");
  server.send(200, "text/plain", "Hello World");  
}


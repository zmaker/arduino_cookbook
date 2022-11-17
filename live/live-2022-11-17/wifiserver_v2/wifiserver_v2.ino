#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "wifipasswords.h"

WebServer server(80);

void setup() {
  pinMode(5, OUTPUT);
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.begin(MY_WIFI_SSID, MY_WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnesso wifi");
  Serial.print("IP:");Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("http://esp32.local/");
  }

  server.on("/", page_index);
  server.on("/on", ledOn);
  server.on("/off", ledOff);
  server.onNotFound(page_error);

  server.begin();
  Serial.println("Server attivo!");
}

void loop() {
  server.handleClient();
  delay(2);
}

void page_index() {
  String str = "Hello ESP32\n";
  str += "URI: ";
  str += server.uri();
  str += "\nargs: ";
  str += server.args();

  server.send(200, "text/plain", str);  
}

void page_error(){
  String str = "Pagina non trovata!\n";
  server.send(404, "text/plain", str);
}

void ledOn(){
  digitalWrite(5, HIGH);
  String str = "ON";
  str += "\nURI: ";
  str += server.uri();
  str += "\nargs: ";
  str += server.args();
  str += "\n";

  for (int i = 0; i < server.args(); i++) {
    str += server.argName(i);
    str += "=";
    str += server.arg(i);
    str += "\n";
  }

  server.send(200, "text/plain", str);
}

void ledOff(){
  digitalWrite(5, LOW);
  String str = "OFF";
  str += "\nURI: ";
  str += server.uri();
  str += "\nargs: ";
  str += server.args();
  for (int i = 0; i < server.args(); i++) {
    str += server.argName(i);
    str += "=";
    str += server.arg(i);
    str += "\n";
  }
  server.send(200, "text/plain", str);
}

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#define STASSID "www.reelco.it"
#define STAPSK  "cardu450IX"

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

const int led = 2;

void setup(void) {
  pinMode(led, OUTPUT);
  for (int i = 0; i < 10; i++) {
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    delay(1000);
  }
  
  Serial.begin(115200);
  Serial.print("setup");
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/on", ledon);
  server.on("/off", ledoff);
  //server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}

void ledon() {  
  server.send(200, "text/plain", "led on");  
  digitalWrite(led, HIGH);
}

void ledoff() {  
  server.send(200, "text/plain", "led off");  
  digitalWrite(led, LOW);
}


#include <WiFi.h>
//#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char* ssid = "wifiname";
const char* password = "wifipass";

WebServer server(80);

void setup(void) {
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);  //station mode: the ESP32 connects to an access point
  //vedi https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/
  
  WiFi.begin(ssid, password);
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //così posso trovare la scheda anche all'indirizzo
  // http://esp32.local/
  if (MDNS.begin("esp32")) {
    Serial.println("Abilito: http://esp32.local/");
  }

  server.on("/", handleRoot);
  server.on("/on", ledOn);
  server.on("/off", ledOff);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks
}

void handleRoot() {  
  server.send(200, "text/plain", "hello from esp32!");
}

void ledOn() {  
  digitalWrite(2, HIGH);
  server.send(200, "text/plain", "LED on");
}

void ledOff() {  
  digitalWrite(2, LOW);
  server.send(200, "text/plain", "LED off");
}


void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  
}

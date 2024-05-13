#include "WiFiS3.h"
#include <ArduinoJson.h>
#include "arduino_secrets.h" 

char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

int status = WL_IDLE_STATUS;
char server[] = "192.168.1.17";  
const int port = 5150;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(1); }

  while (status != WL_CONNECTED) {
    Serial.print(".");
    status = WiFi.begin(ssid, pass);
    delay(3000);
  }

  if (client.connect(server, port)) {
    Serial.print("connesso");
    //GET
    client.println("GET /country/1 HTTP/1.1");
    client.print("Host: ");client.println(server);
    client.println("Connection: close");
    client.println();
  }

}

void loop() {
  read_response();

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    delay(3000);
    Serial.println("disconnecting from Wifi.");
    WiFi.disconnect();

    // do nothing forevermore:
    while (true);
  }
}

void read_response() {
  char status[32];
  client.readBytesUntil('\r', status, sizeof(status));
  // "HTTP/1.0 200 OK" or "HTTP/1.1 200 OK"
  if ((strcmp(status + 9, "201 CREATED") != 0) && (strcmp(status + 9, "200 OK") != 0)) {
    client.stop();
    Serial.println("ERRORE RISPOSTA SRV");
    return;
  }

  char ENDHEAD[] = "\r\n\r\n";
  if (!client.find(ENDHEAD)) {
    client.stop();
    return;
  }

  JsonDocument doc;
  deserializeJson(doc, client);

  int id = doc["country"]["id"];
  const char* name = doc["country"]["name"];
  const char* capital = doc["country"]["capital"];
  int area = doc["country"]["area"];

  Serial.print("ID: ");
  Serial.println(id);
  Serial.print("Nome: ");
  Serial.println(name);
  Serial.print("Capitale: ");
  Serial.println(capital);
  Serial.print("Area: ");
  Serial.println(area);



}
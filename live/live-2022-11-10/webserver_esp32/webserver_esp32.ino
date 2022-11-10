#include <WiFi.h>
#include "wifi_passwords.h"

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(1000);

  analogReadResolution(10);

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nConnesso: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("nuova richiesta");
    String line = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.print(c);
        if (c == '\n') {
          if (line.length() == 0) {
            //genero la risposta di ESP32
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("");

            client.println("<html><head><title>ESP32</title>");
            client.println("<meta http-equiv=\"refresh\" content=\"2;url=http://192.168.1.99/\" />");
            client.println("</head>");
            client.println("<body><h1>Hello ESP32!</h1>");
            int v = analogRead(34);
            client.println("Sensor: ");client.println(v);
            client.println("</body></html>");
            client.println("");

            break;
          } else {
            line = "";
          }
        } else if (c != '\r') {
          line += c;
        }
      }
    }
    client.stop();
    Serial.println("Scollego il client");
  }
}

#include <WiFi.h>
#include "wifi_passwords.h"

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(5, OUTPUT);

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

          if (line.indexOf("GET /on") >= 0) {
            digitalWrite(5, HIGH);
          }
          if (line.indexOf("GET /off") >= 0) {
            digitalWrite(5, LOW);
          }

          if (line.length() == 0) {
            //genero la risposta di ESP32
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("");

            client.println("<html><head><title>ESP32</title>");
            //client.println("<meta http-equiv=\"refresh\" content=\"2;url=http://192.168.1.99/\" />");
            client.println("</head>");
            client.println("<body><h1>Hello ESP32!</h1>");
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

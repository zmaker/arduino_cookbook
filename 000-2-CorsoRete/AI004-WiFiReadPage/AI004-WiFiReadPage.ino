/*
Leggo una pagina
analizza linea per linea e quando trova nella risposta una linea  vuota sa che c'è una pagina
*/
#include <SPI.h>
#include <WiFiNINA.h>

#include "arduino_secrets.h" 
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int keyIndex = 0;           

int status = WL_IDLE_STATUS;
char server[] = "www.zeppelinmaker.it"; 
String page = "/corsoarduino/page1.html";

WiFiClient client;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    delay(1);
  }

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("no module");
    while (true);
  }

  while (status != WL_CONNECTED) {
    Serial.print(".");
    status = WiFi.begin(ssid, pass);
    if (status != WL_CONNECTED) delay(5000);
  }
  Serial.println("\nConnected to WiFi");
  
  Serial.println("\nStarting connection to server...");
    
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("GET "+page+" HTTP/1.1");
    client.println("Host: "+String(server));
    client.println("Connection: close");
    client.println();
  }

  while (true) {
    String line = "";
    bool PAGE = false;
    while (client.available()) {
      char c = client.read();
      if (c == '\n') {
        if (PAGE) Serial.println(line);
        if (line.length() == 0) {
          PAGE = true;  
        }        
        line = "";
      } else if (c != '\r') {
        line += c;
      }      
    }
  
    // if the server's disconnected, stop the client:
    if (!client.connected()) {
      Serial.println();
      Serial.println("disconnecting from server.");
      client.stop();     
      break;   
    }
  }

  Serial.println("disconnecting from wifi.");
  WiFi.disconnect();

  Serial.println("off wifi.");
  WiFi.end();
}

void loop() {
  
}

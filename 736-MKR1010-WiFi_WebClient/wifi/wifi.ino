#include <SPI.h>
#include <WiFiNINA.h>
#include "parameters.h"

char ssid[] = MY_WIFI_SSID;
char pass[] = MY_WIFI_PASS;
int status = WL_IDLE_STATUS;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Web client MKR");

  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    Serial.print(".");
    delay(1000);
  }
  Serial.print("\n");
  Serial.println("connessi al wifi");
  
  if (client.connect("www.zeppelinmaker.it", 80)) {
    client.println("GET /helloworld.txt HTTP/1.1");  
    client.println("Host: www.zeppelinmaker.it");
    client.println("Connection: close");
    client.println();
  }

}

void loop() {
  while (client.available()) {
    char c = client.read();
    Serial.write(c);  
  }

  if (!client.connected()) {
    client.stop();
    Serial.println("disconnesso");
    while(1);  
  }

}

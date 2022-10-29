#include <WiFi.h>
#include "secrets.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.begin(MY_WIFI_SSID, MY_WIFI_PASS);
  delay(2000);

  Serial.println("connecting...");

  while( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\n");
  Serial.println(WiFi.localIP());

  WiFiClient client;
  if (!client.connect("www.zeppelinmaker.it", 80)) {
      Serial.println("non connesso");
      while(true);
  }

  client.println("GET /helloworld.txt HTTP/1.1");
  client.println("Host: www.zeppelinmaker.it");
  client.println("Connection: close");
  client.println("");

  unsigned long t1 = millis();
  while (client.available() == 0) {
    if ((millis() - t1) > 5000){
      client.stop();
      Serial.println("timeout");
      while(true);            
    }
  }

  while(client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  client.println("");
  client.println("close conn");
  client.stop();

}

void loop() {
  // put your main code here, to run repeatedly:

}

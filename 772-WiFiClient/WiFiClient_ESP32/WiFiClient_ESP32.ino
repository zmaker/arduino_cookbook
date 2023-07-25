#include <WiFiS3.h>

void setup() {
  Serial.begin(155200);
  delay(1000);
  Serial.println("Nano ESP32 simple wifi");

  WiFi.begin("www.reelco.it", "pass");
  Serial.println("mi connetto...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  Serial.println("connesso");
  Serial.print("IP: ");Serial.println(WiFi.localIP());

  delay(1000);

  WiFiClient client;
  if (!client.connect("www.zeppelinmaker.it", 80)) {
    Serial.println("non connesso");
    while(true);
  } else {
    client.println("GET /helloworld.txt HTTP/1.1");
    client.println("Host: www.zeppelinmaker.it");
    client.println("Connection: close");
    client.println("");

    unsigned long t1 = millis();
    while (client.available() == 0) {
      if ((millis() - t1) > 5000) {
        Serial.println("timeout");
        client.stop();
        while(true);
      }
    }

    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }

    client.stop();
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}

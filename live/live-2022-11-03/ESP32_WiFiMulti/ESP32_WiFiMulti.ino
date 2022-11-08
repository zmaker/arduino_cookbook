/*
https://docs.espressif.com/projects/arduino-esp32/en/latest/api/wifi.html#wifimulti
*/
#include <WiFi.h>
#include <WiFiMulti.h>
#include "WiFiPasswords.h"

WiFiMulti wifimulti;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Test WiFi Multi");

  wifimulti.addAP(WIFI_SSID_2, WIFI_PASS_2);
  wifimulti.addAP(WIFI_SSID_1, WIFI_PASS_1);
  
  Serial.println("Tento la connessione...");
  if (wifimulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  WiFiClient client;
  if (!client.connect("www.zeppelinmaker.it", 80)){
    while(true);
  }

  //client.println("GET /servizioweb.php?par1=123&temp=23.5&hum=99& HTTP/1.1");  
  //servizi REST

  client.println("GET /helloworld.txt HTTP/1.1");
  client.println("Host: www.zeppelinmaker.it");
  client.println("Connection: close");
  client.println("");

  unsigned long t1 = millis();
  while (client.available() == 0) {
    if ((millis() - t1) > 5000) {
      client.stop();
      while(true);
    }
  }

  while (client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  client.stop();

}

void loop() {
  if (wifimulti.run(5000) == WL_CONNECTED) {
    Serial.print(WiFi.SSID());
    Serial.print("  ");
    Serial.println(WiFi.RSSI());
  } else {
    Serial.println("WiFi not connected!");
  }
  delay(1000);
}

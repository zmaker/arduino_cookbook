// https://github.com/Aircoookie/Espalexa
#include <WiFi.h> 
#include <Espalexa.h>
#include "secrets.h"

Espalexa espalexa;
void lampChanged(uint8_t luminosita);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESPALEXA...");

  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);

  WiFi.mode(WIFI_STA);
  WiFi.begin(MY_WIFI_SSID, MY_WIFI_PASS);
  delay(1000);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  } 

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nconnected!");
    Serial.println(WiFi.localIP());
    espalexa.addDevice("LED 1", lampChanged, 0);

    espalexa.begin();
  } else {
    Serial.println("\nnot connected!");
    while(1);
  }
}

void loop() {
  espalexa.loop();
  delay(1);
}

void lampChanged(uint8_t luminosita){
  Serial.print("lum: ");Serial.println(luminosita);
  if (luminosita) {
    digitalWrite(4, HIGH);    
    Serial.println("ON");
  } else {
    digitalWrite(4, LOW);
    Serial.println("OFF");
  }
}

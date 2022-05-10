#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include "secrets.h"

WiFiMulti wifiMulti;

String url = "https://www.zeppelinmaker.it/service-dati.php?";

void setup() {
    Serial.begin(9600);
    delay(4000);    
    wifiMulti.addAP(WIFI_SSID, WIFI_PASS);

    pinMode(32, INPUT);
    pinMode(19, OUTPUT);
    pinMode(23, OUTPUT);
    Serial.println("ready");
}

void loop() {    
  if((wifiMulti.run() == WL_CONNECTED)) {
    digitalWrite(19, HIGH);
    int bt = digitalRead(32);
    if (bt) {
      digitalWrite(23, HIGH);
      HTTPClient http;    
      int val = analogRead(36);
      http.begin(url+"temp="+String(val));
  
      int code = http.GET();
      Serial.print("code: ");Serial.println(code);
      if (code > 0) {
              // file found at server
              if(code == HTTP_CODE_OK) {
                  String payload = http.getString();
                  Serial.println(payload);
              }
          } else {
              Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(code).c_str());
          }
  
          http.end();
      }
      digitalWrite(23, LOW);
    } else {
      digitalWrite(19, LOW);  
    }
    
}

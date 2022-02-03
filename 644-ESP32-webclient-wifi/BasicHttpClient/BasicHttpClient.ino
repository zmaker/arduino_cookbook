#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

WiFiMulti wifiMulti;


void setup() {
    Serial.begin(9600);
    delay(3000);
    
    wifiMulti.addAP("nomeretewifi", "passwifi");
    Serial.println("pronto");
}

void loop() {
  while (Serial.available()) {
    char ch = Serial.read();  
    if (ch == 's') {
      Serial.println("connect...");
      getPage();
    }   
  }
}

void getPage() {
  if((wifiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;
    http.begin("http://www.zeppelinmaker.it/helloworld.txt");

    // start connection and send HTTP header
    int httpCode = http.GET();
    Serial.printf("HTTP code: %d\n", httpCode);

    // httpCode will be negative on error
    if (httpCode > 0) {            
      if (httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          Serial.println(payload);
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }
}

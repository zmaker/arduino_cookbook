#include <WiFi.h>
#include <HTTPClient.h>

unsigned long t1;

void setup() {
  Serial.begin(115200);
  Serial.println("wifi basic 1");
  delay(1000);

  WiFi.begin("nomerete", "password");
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }  

  Serial.print("\n IP: ");
  Serial.println(WiFi.localIP());

  t1 = millis();
}

void loop() {
  if ((millis() - t1) > 5000) {
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      String addr = "https://httpbin.org/get?temp=23.4&hum=45&color=red&"; 
      http.begin(addr.c_str());
      //http.setAuthorization("SRV_LOGIN","SRV_PASS");
      int code = http.GET();

      Serial.print("HTTP CODE: ");Serial.println(code);
      if (code == 200) {
        String resp = http.getString();
        Serial.println(resp);
      }
    } else {
      WiFi.disconnect();
      WiFi.reconnect();
    }
    http.end();
    t1 = millis();
  }
}



#include <WiFi.h>

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

  delay(3000);

  WiFi.disconnect();
  Serial.println("wifi scollegato");
}

void loop() {
  // put your main code here, to run repeatedly:

}

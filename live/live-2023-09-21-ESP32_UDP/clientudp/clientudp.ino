#include <WiFi.h>
#include <WiFiUdp.h>

WiFiUDP udp;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Client UDP");

  WiFi.begin("reelco_2_4", "cardu450IX");
  Serial.println("mi connetto...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nconnesso");
  Serial.print("IP: ");Serial.println(WiFi.localIP());
  delay(1000);

  udp.begin(1234);
}

void loop() {
  uint8_t buffer[20] = "hello UDP!";
  udp.beginPacket("192.168.1.111", 1234);
  udp.write(buffer, 10);
  udp.endPacket();
  Serial.println("u");
  delay(2000);
}

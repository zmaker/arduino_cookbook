#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xD4, 0xB1 };

EthernetServer server(1234);

void setup() {
  Ethernet.begin(mac);
  Serial.begin(9600);

  Serial.print("Indirizzo ip del server: ");
  Serial.println(Ethernet.localIP());

  server.begin();

}

void loop() {
  EthernetClient client = server.available();  
  if (client) {
    if (client.available() > 0) {
      char ch = client.read();
      String str = String(ch);
      Serial.println(str);
    }
  }
}

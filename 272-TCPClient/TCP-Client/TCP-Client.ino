#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0x90, 0xAE, 0xA2, 0x01, 0x02, 0x03};
byte server[] = {192, 168, 1, 147};

EthernetClient client;

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac);
  Serial.print("Indirizzo IP del client: ");
  Serial.println(Ethernet.localIP());

  if (client.connect(server, 1234)) {
    Serial.println("connesso");
  }
}


int n = 0;
void loop() {
  if (client.connected()) {
    client.write(n);
    delay(1000);

    if (n == 100) {
      client.stop();  
    }
    n++;
  }   
}

#include <Ethernet.h>
#include <EthernetUdp.h>

byte mac[] = { 0x90, 0xA2, 0x01, 0x02, 0x03, 0x04 };
IPAddress ip(192, 168, 1, 147);

unsigned int localPort = 8888;   

char buff[UDP_TX_PACKET_MAX_SIZE];

EthernetUDP Udp;

void setup() {
  Serial.begin(9600);
  Ethernet.init(10); //CS 

  Ethernet.begin(mac, ip);

  Serial.print("Indirizzo di Arduino: ");
  Serial.println(Ethernet.localIP());

  Udp.begin(localPort);
}

void loop() {
  int datalen = Udp.parsePacket();
  if (datalen) {
      Serial.print("Received packet of size ");
      Serial.println(datalen);
      Serial.print("From: ");
      IPAddress remote = Udp.remoteIP();
      for (int i = 0 ; i < 4; i++) {
        Serial.print(remote[i], DEC);
        if (i < 3) {
          Serial.print(".");
        }
      }
      Serial.println(" ");

      Udp.read(buff, UDP_TX_PACKET_MAX_SIZE);
      Serial.println("Contents:");
      Serial.println(buff);
  }
  delay(10);
}

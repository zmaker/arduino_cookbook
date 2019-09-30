#include <Ethernet.h>
#include <EthernetUdp.h>

byte mac[] = {0x90, 0xAA, 0xDA, 0x01, 0x02, 0x03};
char buff[20];

EthernetUDP Udp;

IPAddress remote(192, 168, 178, 143);
unsigned int remotePort = 8888;

void setup() {
  Serial.begin(9600);
  Ethernet.init(10);
  if (Ethernet.begin(mac) == 0) {}
  
  Serial.print("Indirizzo di Arduino: ");
  Serial.println(Ethernet.localIP());

  Udp.begin(8000);
}

int n = 0;

void loop() {
  Serial.print("tx: ");
  Serial.println(n);

  String msg = String(n);
  msg.toCharArray(buff, 20);

  Udp.beginPacket(remote, remotePort);
  Udp.write(buff);
  Udp.endPacket();

  n++;
  delay(1000);
}

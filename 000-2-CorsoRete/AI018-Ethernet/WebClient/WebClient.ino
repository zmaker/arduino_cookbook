#include <SPI.h>
#include <Ethernet.h>
//#include <WiFiNINA.h>

char server[] = "www.zeppelinmaker.it";
char page[] = "/helloworld.txt";

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xD4, 0xB1 };
//IPAddress ip(192, 168, 0, 177);
//IPAddress myDns(192, 168, 0, 1);
EthernetClient client;
//WiFiClient client;

void setup() {
  Ethernet.init(10);
  
  Serial.begin(9600);
  while (!Serial) {
     delay(1);  
  }

  if (Ethernet.begin(mac) == 0) {
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.");
      while (true);
    }
    
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
  
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    //Ethernet.begin(mac, ip, myDns);
    while (true);
    
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }

  //End connessione

  if (client.connect(server, 80)) {
    Serial.println("Collegato al server web");
    String req = "GET "+String(page)+" HTTP/1.1";
    client.println(req);
    client.println("Host: "+String(server));
    client.println("Connection: close");
    client.println();
  }

  while(true) {
    while (client.available()) {
      char c = client.read();
      Serial.write(c);  
    }

    if (!client.connected()) {
      Serial.println("\n\nScollegato dal server web");
      client.stop();
      break;
    }
  }  
}

void loop() {
  // put your main code here, to run repeatedly:

}

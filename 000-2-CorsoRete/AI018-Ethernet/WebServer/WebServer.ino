#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xD4, 0xB1 };
//IPAddress ip(192, 168, 5, 1);
EthernetServer server(80);

void setup() {
  Ethernet.init(10);  
  
  Serial.begin(9600);
  while (!Serial) {
     delay(1);  
  }

  //Ethernet.begin(mac, ip);
  Ethernet.begin(mac);

  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }
  
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

String line = "";

void loop() {
  EthernetClient client = server.available();
  if (client) {
    while(client.connected()) {
      if (client.available()) {
        char c = client.read();
        //Serial.write(c);  
        
        if (c == '\n'){
          Serial.println(line);
          if (line.length() == 0) {
            Serial.println("\nRESP\n");
            response(&client);
            break;
          }
          
          line = "";
        } else if (c != '\r'){
          line += c;
        }
        
      }
    }
    delay(1);
    client.stop();  
  }
}

void response(EthernetClient *client){
  client->println("HTTP/1.1 200 OK");
  client->println("Content-Type: text/html"); 
  client->println("Connection: close"); 
  client->println(); 
  client->println("<!DOCTYPE HTML>"); 
  client->println("<HTML>"); 
  client->println("<BODY><h1>hello from ETH Server</h1></BODY>"); 
  client->println("</HTML>"); 
}

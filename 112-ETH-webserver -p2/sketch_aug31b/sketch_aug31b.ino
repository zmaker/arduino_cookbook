#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xD4, 0xB1 };
IPAddress ip(192, 168, 1, 100);

//crea un server ETH sulla porta 80
EthernetServer server(80);


void setup() {
  Serial.begin(9600);

  Ethernet.begin(mac);
  server.begin();
  Serial.print("server IP: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  EthernetClient client = server.available();
  if (client) {
      boolean blank = true;
      while (client.connected()) {
          if (client.available()) {
               char c = client.read();
               Serial.print(c);  

               if ((c == '\n') && blank){
                  client.println("HTTP/1.1 200 OK");
                  client.println("Content-Type: text/html");
                  client.println("Connection: close");  // the connection will be closed after completion of the response
                  //client.println("Refresh: 5");  // refresh the page automatically every 5 sec
                  client.println();
                  client.println("<!DOCTYPE HTML>");
                  client.println("<html>");
                  client.println("<H1>Hello Arduino!</H1>");                  
                  client.println("</html>");
                  break;
               }

               if (c == '\n') {
                   blank = true; 
               } else if (c != '\r') {
                   blank = false; 
               }
          }   
      }
      delay(1);
      client.stop();
      Ethernet.maintain();
  }
}





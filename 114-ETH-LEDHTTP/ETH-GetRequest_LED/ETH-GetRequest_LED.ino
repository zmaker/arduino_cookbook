/*
  Web Server - processa richieste GET
 */

#include <SPI.h>
#include <Ethernet.h>

#define LED 7

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xD4, 0xB1 };
IPAddress ip(192, 168, 1, 100);

//crea un server ETH sulla porta 80
EthernetServer server(80);

void setup() {
  pinMode(LED, OUTPUT);
  
  Serial.begin(9600);
  while (!Serial) {}
  
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server IP: ");
  Serial.println(Ethernet.localIP());
}

int stato = LOW;

void loop() {
  EthernetClient client = server.available();
  if (client) {
    Serial.println("nuova connessione!");
    
    boolean currentLineIsBlank = true;

    String line = String();
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        //Serial.write(c);

        line.concat(c);
        
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");

          client.println("<H1>Led is: ");
          if (stato) {
            client.println("ON");
          } else {
            client.println("OFF");
          }
          client.println("</H1>");
          client.println("</html>");
          break;
        }
        
        if (c == '\n') {
          //nuova riga
          currentLineIsBlank = true;
          Serial.print(line);

          if (line.indexOf("ledon") >= 0) {
              stato = HIGH;              
          }
          if (line.indexOf("ledoff") >= 0) {              
              stato = LOW;
          }          
          
          line = String();
        } else if (c != '\r') {
          // la riga non è vuota
          currentLineIsBlank = false;
        }
      }      
    }  
    digitalWrite(LED, stato);  
    delay(1);    
    client.stop();
    Serial.println("client disconnected");
    Ethernet.maintain();
  }
}


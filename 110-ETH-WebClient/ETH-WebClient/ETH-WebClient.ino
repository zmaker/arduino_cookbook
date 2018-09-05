/*
  Web client

 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe, based on work by Adrian McEwen

 */

#include <SPI.h>
#include <Ethernet.h>

char server[] = "www.google.com"; 

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xD4, 0xB1 };
IPAddress ip(192, 168, 1, 100);

EthernetClient client;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
  }
  Serial.println("ready!");

  //richiede l'indirizzo IP
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }
  delay(1000);
  Serial.println("connecting...");

  // avvia la connessione al server di google
  if (client.connect(server, 80)) {
    Serial.println("connected");
    //Comandi HTTP
    //effettua la ricerca
    client.println("GET /search?q=arduino HTTP/1.1"); 
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();
  } else {    
    Serial.println("connessione fallita!");
  }
}

void loop() {
  if (client.available()) {
    //legge i dati inviati dal server
    char c = client.read();
    Serial.print(c);
  }

  //al termine della trasmissione si disconnette
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    //si blocca per sempre
    while (true);
  }
}


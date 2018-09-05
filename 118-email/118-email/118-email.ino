#include <SPI.h>
#include <Ethernet.h>

char server[] = "www.zeppelinmaker.it"; 

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0x00, 0x00 };
IPAddress ip(192, 168, 1, 100);

EthernetClient client;

void setup() {
  Serial.begin(9600);
  Serial.println("ready!");
  
  Ethernet.begin(mac);  
  
  delay(1000);

  pinMode(7, INPUT);  
}

void loop() {
  if (digitalRead(7)) {
    Serial.println("connecting...");  
    if (client.connect(server, 80)) {
      Serial.println("connected");
      //Comandi HTTP
      //effettua la ricerca
      client.println("GET /mail.php?to=mario@rossi.it&msg=Hello World HTTP/1.1"); 
      client.print("Host: ");
      client.println(server);
      client.println("Connection: close");
      client.println();
    } else {    
      Serial.println("connessione fallita!");
    }  
    
  }

  //risposta dal server
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


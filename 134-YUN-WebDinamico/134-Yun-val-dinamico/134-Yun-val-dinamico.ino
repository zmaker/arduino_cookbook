/*
Pubblica dati dinamici
all'indirizzo:

http://arduino.local/arduino/temperatura

 */

#include <Bridge.h>
#include <YunClient.h>
#include <YunServer.h>

YunServer server;

void setup() {  
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);
  //quando è pronto si accende il LED13
  
  Serial.println("pronti!");  
  server.listenOnLocalhost();
  server.begin();
}

void loop() {   
  YunClient client = server.accept();

  if (client) {
    String command = client.readString();
    command.trim();

    if (command == "temperatura") {
      int val = analogRead(A0);
      client.print(val);  
    }

    client.stop();
  }

  delay(50);
}



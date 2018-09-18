/*
crea due servizi:
http://arduino.local/arduino/ledon
http://arduino.local/arduino/ledoff

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
  
  delay(2000);
  digitalWrite(13, LOW);
}

void loop() {   
  YunClient client = server.accept();

  if (client) {
    String command = client.readString();
    command.trim();

    if (command == "ledon") {
      digitalWrite(13, HIGH);
    }
    if (command == "ledoff") {
      digitalWrite(13, LOW);
    }

    client.stop();
  }

  delay(50);
}



/*
legge una pagina web

Arduino YUN va collegato via ETH a internet e con la seraiel a un pC
*/

#include <Bridge.h>
#include <HttpClient.h>

void setup() {
  SerialUSB.begin(9600);
  while (!SerialUSB); 
  
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);

  SerialUSB.print("pronti!");
}

void loop() {  
  HttpClient client;
  
  client.get("http://www.zeppelinmaker.it/helloworld.txt");

  while (client.available()) {
    char c = client.read();
    SerialUSB.print(c);
  }
  SerialUSB.flush();

  delay(5000);
}



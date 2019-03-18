/*
* https://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/
* https://github.com/nRF24/RF24
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte addresses[][6] = {"00001", "00002"};


void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);  
  radio.begin();
  //indirizzi sono assegnati invertiti
  radio.openWritingPipe(addresses[0]); 
  radio.openReadingPipe(1, addresses[1]); 
  radio.setPALevel(RF24_PA_MIN);
}
void loop() {
  delay(5);
  radio.startListening();
  
  if ( radio.available()) {
    while (radio.available()) {
      int led = LOW;
      radio.read(&led, sizeof(led));
      digitalWrite(2, led);
    }
    delay(5);
    radio.stopListening();
    int bt = digitalRead(3);
    radio.write(&bt, sizeof(bt));
  }
  
}

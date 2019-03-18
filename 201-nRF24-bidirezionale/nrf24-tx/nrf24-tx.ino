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
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  radio.begin();
  radio.openWritingPipe(addresses[1]); 
  radio.openReadingPipe(1, addresses[0]); 
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  delay(5);
  radio.stopListening();
    
  int bt = digitalRead(3);  
  Serial.print("bt:"); Serial.println(bt);  
  radio.write(&bt, sizeof(bt));
  delay(5);
  
  radio.startListening();

  int remoteBt = LOW;
  while (radio.available()) {
    radio.read(&remoteBt, sizeof(remoteBt));  
  }
  Serial.print("led:"); Serial.println(remoteBt);  
  digitalWrite(2, remoteBt); 
  
}

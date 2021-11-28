/*
* https://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/
* https://github.com/nRF24/RF24
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

int stato = 0;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
 
  Serial.begin(9600);
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {  
  //trasmette 0, 1, 2
  stato = 0;
  digitalWrite(2, LOW); 
  digitalWrite(3, HIGH);  
  radio.write(&stato, sizeof(stato));
  delay(5000);
  stato = 1;  
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);  
  radio.write(&stato, sizeof(stato));
  delay(5000);
  stato = 2;  
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);  
  radio.write(&stato, sizeof(stato));
  delay(5000);
}

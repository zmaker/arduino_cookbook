/*
* https://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/
* https://github.com/nRF24/RF24
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

int stato = 0;

void loop() {  
  //trasmette 0 e 1
  Serial.println(stato);
  radio.write(&stato, sizeof(stato));
  delay(1000);
  stato = !stato;
}

#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK mod;

uint8_t buff[30];
uint8_t buflen = 12;

void setup() {
  Serial.begin(9600);
  Serial.println("433MHz-RX-STR");
  
  if (!mod.init()) {
    Serial.println("init failed");
    while(1);
  }

}

void loop() {
  if (mod.recv(buff, &buflen)) {
    buff[buflen] = '\0';
    Serial.print("len: "); Serial.print(buflen);
    Serial.print(" - ");Serial.println((char *)buff);   
    mod.printBuffer("RX: ", buff, buflen);
  }

}

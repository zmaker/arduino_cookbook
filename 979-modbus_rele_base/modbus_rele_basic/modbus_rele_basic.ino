#include <RS485.h>
#include <SoftwareSerial.h>

#define RX_PIN 4
#define TX_PIN 2
#define CTRL_PIN 3

SoftwareSerial rs485Serial(RX_PIN, TX_PIN);
RS485 rs485(&rs485Serial, CTRL_PIN);

/*
0xFF	Indirizzo slave - non è un indirizzo valido! Andrebbe reimpostato con un valore tra 1 e 247 - 0 broadcast
0x05	Function code = Write Single Coil
0x00 0x00	Indirizzo coil = 0
0xFF 0x00	Valore da scrivere = ON
0x99 0xE4	CRC Modbus
*/
uint8_t frame[] =  {0xFF, 0x05, 0x00, 0x00, 0xFF, 0x00, 0x99, 0xE4};  //relè on
uint8_t frame2[] = {0xFF, 0x05, 0x00, 0x00, 0x00, 0x00, 0xD8, 0x14};  //relè off

void setup() {
  Serial.begin(115200);
  rs485Serial.begin(9600);

  rs485.setMicrosPerByte(1100);
  Serial.println("RS485 rele 1");
}

void loop() {
  rs485.write(frame, sizeof(frame));
  rs485.flush();
  delay(2000);
  rs485.write(frame2, sizeof(frame2));
  rs485.flush();
  delay(2000);
}

#include <Wire.h>
#define disk1 0x50

void setup() {
  Serial.begin(9600);
  Wire.begin();

  unsigned int addr = 0;
  Serial.println("scrivo la EEPROM");
  writeEEPROM(disk1, addr, 123);
  Serial.println("leggo la EEPROM");
  int n = readEEPROM(disk1, addr);
  Serial.println(n);
}

void loop() {}

void writeEEPROM(int i2caddr, unsigned int maddr, byte data){
  Wire.beginTransmission(i2caddr);
  Wire.write((int)(maddr >> 8));
  Wire.write((int)(maddr & 0xFF));
  Wire.write(data);
  Wire.endTransmission();
  delay(5);
}

byte readEEPROM(int i2caddr, unsigned int maddr){
  Wire.beginTransmission(i2caddr);
  Wire.write((int)(maddr >> 8));
  Wire.write((int)(maddr & 0xFF)); 
  Wire.endTransmission();

  Wire.requestFrom(i2caddr, 1);
  byte rdata = 0;
  if (Wire.available()) {
     rdata = Wire.read(); 
  }
  return rdata;
}





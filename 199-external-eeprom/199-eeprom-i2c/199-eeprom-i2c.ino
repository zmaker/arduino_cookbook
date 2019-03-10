//http://www.hobbytronics.co.uk/arduino-external-eeprom

#include <Wire.h>    
 
#define disk1 0x50    //Address of 24LC256 eeprom chip
 
void setup(void) {
  Serial.begin(9600);
  Wire.begin();  
 
  unsigned int address = 0;
  Serial.println("writing EEPROM...");
  writeEEPROM(disk1, address, 123);
  delay(1000);
  Serial.println("reading EEPROM...");
  Serial.print(readEEPROM(disk1, address), DEC);
}
 
void loop(){}
 
void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data ) {
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(data);
  Wire.endTransmission();
  delay(5);
}
 
byte readEEPROM(int deviceaddress, unsigned int eeaddress ) {
  byte rdata = 0xFF;
 
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();
 
  Wire.requestFrom(deviceaddress,1);
 
  if (Wire.available()) rdata = Wire.read();
 
  return rdata;
}

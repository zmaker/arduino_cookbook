// This sketch tests the standard 7-bit addresses
// and looks for addresses 0x20 to 0x27 -> PCF8574
// or addresses 0x38 to 0x3F -> PCF8574A
//

#include <Wire.h>


void setup()
{
  Wire.begin();

  Serial.begin(9600);
  while (!Serial);             // wait for serial monitor
  delay(200);
  Serial.println("\nPCF8574 ADRRESS SCANNER");
}


void loop()
{
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    //if (error == 0 && (address == 0x20 || address == 0x38) )
    if (error == 0 && ((address >= 0x20 && address <=0x27) || (address >= 0x38 && address <= 0x3F)) )
    {
      Serial.print("PCF8574 device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println(" !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknow error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No PCF8574 devices found at 0x20 or 0x38 addresses\n");
  else
    Serial.println();

  delay(5000);           // wait 5 seconds for next scan
}

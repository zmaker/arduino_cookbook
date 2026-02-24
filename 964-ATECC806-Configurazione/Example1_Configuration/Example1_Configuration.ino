
/*
  Using the SparkFun Cryptographic Co-processor Breakout ATECC508a (Qwiic)
  By: Pete Lewis
  SparkFun Electronics
  Date: August 5th, 2019
  License: This code is public domain but you can buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Please buy a board from SparkFun!
  https://www.sparkfun.com/products/15573

  This example shows how to setup your Cryptographic Co-processor with SparkFun's standard settings.
  ***Configurations settings are PERMENANT***
  We highly encourage advanced users to do their own configuration settings.

  Hardware Connections and initial setup:
  Install artemis in boards manager: http://boardsmanager/All#Sparkfun_artemis
  Plug in your controller board (e.g. Artemis Redboard, Nano, ATP) into your computer with USB cable.
  Connect your Cryptographic Co-processor to your controller board via a qwiic cable.
  Select TOOLS>>BOARD>>"SparkFun Redboard Artemis"
  Select TOOLS>>PORT>> "COM 3" (note, yours may be different)
  Click upload, and follow configuration prompt on serial monitor at 115200.

*/

#include <SparkFun_ATECCX08a_Arduino_Library.h> //Click here to get the library: http://librarymanager/All#SparkFun_ATECCX08a
#include <Wire.h>

ATECCX08A atecc;


void setup() {
  // Arduino
  //Wire.begin();

  //ESP32
  Wire.begin(21, 22);
  Wire.setClock(10000);
  delay(1000);
  
  Serial.begin(115200);
  if (atecc.begin() == true)
  {
    Serial.println("Successful wakeUp(). I2C connections are good.");
  }
  else
  {
    Serial.println("Device not found. Check wiring.");
    while (1); // stall out forever
  }

  printInfo(); // see function below for library calls and data handling

  Serial.println("Would you like to configure your Cryptographic Co-processor with SparkFun Standard settings? (y/n)");
  Serial.println("***Note, this is PERMANENT and cannot be changed later***");
  Serial.println("***If you do not want to do this, type an 'n' or unplug now.***");

  while (Serial.available() == 0); // wait for user input

  if (Serial.read() == 'y')
  {
    Serial.println();
    Serial.println("Configuration beginning.");

    Serial.print("Write Config: \t");
    if (atecc.writeConfigSparkFun() == true) Serial.println("Success!");
    else Serial.println("Failure.");

    Serial.print("Lock Config: \t");
    if (atecc.lockConfig() == true) Serial.println("Success!");
    else Serial.println("Failure.");

    Serial.print("Key Creation: \t");
    if (atecc.createNewKeyPair() == true) Serial.println("Success!");
    else Serial.println("Failure.");

    Serial.print("Lock Data-OTP: \t");
    if (atecc.lockDataAndOTP() == true) Serial.println("Success!");
    else Serial.println("Failure.");

    Serial.print("Lock Slot 0: \t");
    if (atecc.lockDataSlot0() == true) Serial.println("Success!");
    else Serial.println("Failure.");

    Serial.println("Configuration done.");
    Serial.println();
  }
  else
  {
    Serial.println("Unfortunately, you cannot use any features of the ATECCX08A without configuration and locking.");
  }

  printInfo(); // Print info again to see lock statuses. And if all is good, print the generated public key!
}

void loop()
{
  // do nothing.
}

void printInfo()
{
  // Read all 128 bytes of Configuration Zone
  // These will be stored in an array within the instance named: atecc.configZone[128]
  atecc.readConfigZone(false); // Debug argument false (OFF)

  // Print useful information from configuration zone data
  Serial.println();

  Serial.print("Serial Number: \t");
  for (int i = 0 ; i < 9 ; i++)
  {
    if ((atecc.serialNumber[i] >> 4) == 0) Serial.print("0"); // print preceeding high nibble if it's zero
    Serial.print(atecc.serialNumber[i], HEX);
  }
  Serial.println();

  Serial.print("Rev Number: \t");
  for (int i = 0 ; i < 4 ; i++)
  {
    if ((atecc.revisionNumber[i] >> 4) == 0) Serial.print("0"); // print preceeding high nibble if it's zero
    Serial.print(atecc.revisionNumber[i], HEX);
  }
  Serial.println();

  Serial.print("Config Zone: \t");
  if (atecc.configLockStatus) Serial.println("Locked");
  else Serial.println("NOT Locked");

  Serial.print("Data/OTP Zone: \t");
  if (atecc.dataOTPLockStatus) Serial.println("Locked");
  else Serial.println("NOT Locked");

  Serial.print("Data Slot 0: \t");
  if (atecc.slot0LockStatus) Serial.println("Locked");
  else Serial.println("NOT Locked");

  Serial.println();

  // if everything is locked up, then configuration is complete, so let's print the public key
  if (atecc.configLockStatus && atecc.dataOTPLockStatus && atecc.slot0LockStatus) 
  {
    if(atecc.generatePublicKey() == false)
    {
      Serial.println("Failure to generate This device's Public Key");
      Serial.println();
    }
  }
}
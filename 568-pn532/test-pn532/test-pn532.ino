/*
PN532 - 
https://learn.adafruit.com/adafruit-pn532-rfid-nfc/arduino-library
*/

/**************************************************************************/
#include <Wire.h>
#include <Adafruit_PN532.h>

#define PN532_IRQ   (2)
#define PN532_RESET (3)  // Not connected by default on the NFC Shield
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

void setup(void) {
  Serial.begin(9600);
  Serial.println("Hello!");

  
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  
  nfc.SAMConfig();
   
}

char buf[4];

void loop(void) {
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
    
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  
  if ((success) && (uidLength == 4)) {
    Serial.println("ok");
    for (int i = 0; i < 4; i++) {  
      sprintf(buf, "%03u", uid[i]);    
      Serial.println(uid[i]);  
    }
    Serial.println("");
    delay(1000);
  }
}

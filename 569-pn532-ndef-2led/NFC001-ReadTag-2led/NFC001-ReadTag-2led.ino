/*
 * librerie NDEF 
 * https://github.com/don/NDEF
 * e richiede anche
 * https://github.com/Seeed-Studio/PN532
*/
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

void setup(void) {
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
    Serial.begin(9600);
    Serial.println("NDEF Reader");
    nfc.begin();
}

void loop(void) {    
    if (nfc.tagPresent()) {
        NfcTag tag = nfc.read();
        String id = tag.getUidString();
        Serial.print("id="); 
        Serial.print(id);
        Serial.println("#");
        //tag.print();

        checkTag(id);
    }
    delay(5000);
}

int L4, L5 = LOW;

void checkTag(String id) {
  if (id == "C0 F8 69 25"){
    L4 = !L4; 
    digitalWrite(4, L4);     
  } else if (id == "2A 1C 97 16"){
    L5 = !L5;
    digitalWrite(5, L5);      
  }  
}

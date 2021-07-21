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
  pinMode(6, INPUT);
  Serial.begin(9600);
  Serial.println("NDEF Reader");
  nfc.begin();
}

int stato = 0;

void loop(void) {    

  if (digitalRead(6)) {
    digitalWrite(4, HIGH);
    if (nfc.tagPresent()) {    
      digitalWrite(5, HIGH);
      Serial.print("CLEAN:");
      int success = nfc.clean();
      Serial.println(success);

      delay(1000);
      Serial.print("FORMAT:");
      success = nfc.format();
      Serial.println(success);

      delay(1000);
      Serial.print("WRITE:");
      NdefMessage message = NdefMessage();
      message.addTextRecord("Hello, Arduino!");
      success = nfc.write(message);
      Serial.println(success);   
      delay(1000);
      digitalWrite(5, LOW);
    }
    digitalWrite(4, LOW);
  }
  
}

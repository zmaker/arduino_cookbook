#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  Serial.println("Avvicina un tag per la lettura");
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.println("ID CARTA: ");
    String uid = "";
    for (int i = 0; i < mfrc522.uid.size; i++) {
      uid += String(mfrc522.uid.uidByte[i], HEX) + " ";      
    } 
    Serial.println(uid);

    //lettura dati su tag
    byte data[70];
    byte buffer[18];
    byte size = sizeof(buffer);
    byte addr = 0;

    for (int i = 0; i < 3; i++) {
      addr = i*4;  
      MFRC522::StatusCode status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(addr, buffer, &size);
      if (status != MFRC522::STATUS_OK) {
          Serial.print(F("MIFARE_Read() failed: "));
          Serial.println(mfrc522.GetStatusCodeName(status));
      }
      Serial.print("Dati del blocco: ");Serial.println(addr);
      dump_byte_array(buffer, 16);

      for (int j = 0; j < 16; j++) {
        data[j+(addr * 4)] = buffer[j];  
      }
    }

    for (int i = 0; i < 64; i++) {
      Serial.print(data[i], HEX);
      Serial.print(" ");      
    }
    Serial.print("\n");
    for (int i = 23; i < 64; i++) {
      if (data[i] == 0xFE) break;
      char c = data[i];
      Serial.print(c);
      Serial.print(" ");      
    }
    Serial.print("\n");
     
    mfrc522.PICC_HaltA();
  }
}

void dump_byte_array(byte *buffer, byte bufferSize) {
  for (int i = 0; i < bufferSize; i++){
    Serial.print( (buffer[i] < 0x10 ? " 0" : " " ) );
    Serial.print( buffer[i], HEX );  
    if ( (i%4) == 3 ) Serial.print("\n");
  }
    
}

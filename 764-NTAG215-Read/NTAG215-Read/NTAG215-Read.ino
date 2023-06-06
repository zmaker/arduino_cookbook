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
    byte buffer[18]; 
    byte size = sizeof(buffer);
    uint8_t addr = 0x06;

    MFRC522::StatusCode status;
    status = mfrc522.MIFARE_Read(addr, buffer, &size);
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("MIFARE_Read() failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;      
    }
    Serial.println("Dati letti:");
    for (int i = 0; i < 16; i++) {
      Serial.write(buffer[i]);  
    }
    Serial.println(" ");
    
    mfrc522.PICC_HaltA();
  }
}

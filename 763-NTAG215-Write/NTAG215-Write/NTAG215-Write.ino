#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  Serial.println("Avvicina un tag per la scrittura");
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.println("ID CARTA: ");
    String uid = "";
    for (int i = 0; i < mfrc522.uid.size; i++) {
      uid += String(mfrc522.uid.uidByte[i], HEX) + " ";      
    } 
    Serial.println(uid);

    //scrittura dati su tag
    byte buffer[18]; 
    byte size = sizeof(buffer);
    uint8_t addr = 0x06;

    memcpy(buffer, "Hello World!....", 16);
    MFRC522::StatusCode status;

    for (int i = 0; i < 4; i++){
      status = mfrc522.MIFARE_Ultralight_Write(addr+i, &buffer[i*4], 4);
      if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Read() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }
    }
    Serial.println("Scrittura terminata...");
    
    mfrc522.PICC_HaltA();
  }
}

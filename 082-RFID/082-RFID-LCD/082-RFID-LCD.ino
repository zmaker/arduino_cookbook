/*
  https://github.com/miguelbalboa/rfid/blob/master/src/MFRC522.h

  RC522_RFID_Module_Example

  Collegamenti:
  SDA             D10
  SCK             D13
  MOSI            D11
  MISO            D12
  GND             GND
  RST             D9
  3.3V            3.3V

*/

#include <SPI.h>
#include <MFRC522.h>
/* Vengono definiti PIN del RFID reader*/
#define SS_PIN 10  // 53 per Arduino Mega
#define RST_PIN 9

/* Viene creata una istanza della RFID libreria */
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  //led di segnalazione
  pinMode(2, OUTPUT);

  Serial.begin(9600);
  /* Abilita SPI*/
  SPI.begin();
  /* Viene inizilizzato RFID reader */  
  mfrc522.PCD_Init();    // Initialize MFRC522 Hardware
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    digitalWrite(2, HIGH);
    delay(300);
    digitalWrite(2, LOW);
  }
  Serial.println();
  delay(1000);
}


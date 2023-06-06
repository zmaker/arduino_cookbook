#include <SPI.h>
#include <MFRC522.h>

MFRC522 reader(10, 9);  //SS e RST

void setup() {
  Serial.begin(9600);
  SPI.begin();
  reader.PCD_Init();
  delay(10);
  Serial.println("RC522 pronto");
}

void loop() {
  if (reader.PICC_IsNewCardPresent() && reader.PICC_ReadCardSerial()) {
    String uid = getUID();
    Serial.print("UID: ");
    Serial.println(uid);
  }
  delay(10);
}

String getUID() {
  String ret = "";
  for (int i = 0; i < reader.uid.size; i++) {
    ret += String(reader.uid.uidByte[i], HEX) + " ";
  }
  reader.PICC_HaltA();
  return ret;
}

#include <SparkFun_ATECCX08a_Arduino_Library.h> 
#include "Wire.h"

ATECCX08A atecc;
uint8_t publicKey[64];

void setup() {
  Wire.begin();
  delay(100);
  while (!Serial);
  Serial.begin(9600);
  Serial.println("Genera KeyPair");

  if (!atecc.begin()) {
    Serial.println("errore i2c?");
    while(true);
  }

  atecc.createNewKeyPair(1); //slot n.1
  char buf[10];
  for (int i = 0; i < 64; i++) {
    sprintf(buf, "0x%02X, ", atecc.publicKey64Bytes[i]);
    Serial.print(buf);
  }
  Serial.println("");
}

void loop() {
  // put your main code here, to run repeatedly:

}

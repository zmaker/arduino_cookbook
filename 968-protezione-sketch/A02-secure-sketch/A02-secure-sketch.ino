#include <SparkFun_ATECCX08a_Arduino_Library.h> 
#include "Wire.h"

ATECCX08A atecc;
uint8_t challenge[32];
uint8_t signature[64];
uint8_t publicKey[64];
uint8_t authorizedKey[64] = {
  0x71, 0x44, 0xCE, 0xB1, 0x3C, 0x92, 0x17, 0x53, 
  0x4F, 0x85, 0x1B, 0x72, 0xC2, 0x83, 0x97, 0xCF, 
  0xF8, 0xCE, 0x0D, 0x31, 0x02, 0xBB, 0x6B, 0xCF, 
  0x7C, 0x49, 0x97, 0x7B, 0x0D, 0x48, 0x9E, 0x9A, 
  0xB1, 0xC6, 0x5E, 0x8D, 0xAE, 0x2A, 0x2D, 0x21, 
  0xBB, 0x72, 0xAB, 0xBB, 0x38, 0x39, 0x36, 0x2C, 
  0xEB, 0xA5, 0x63, 0xFD, 0x0B, 0x86, 0x38, 0x7D, 
  0xFF, 0x45, 0x41, 0x60, 0x50, 0xC2, 0xE9, 0x73
};

void setup() {
  Wire.begin();
  delay(100);
  while (!Serial);
  Serial.begin(9600);
  Serial.println("Sketch con licenza");

  if (!atecc.begin()) {
    Serial.println("errore i2c?");
    while(true);
  }

  if (!checkLicense()) {
    Serial.println("licenza non valida");
    //disabilio il device
    while(1);
  }

  if (!isAuthorized()) {
    Serial.println("licenza non autorizzata");
    //disabilio il device
    while(1);
  }

  Serial.println("Ok, run possibile");
}

void loop() {
  // put your main code here, to run repeatedly:

}

bool checkLicense(){
  //1. genero challenge
  for (int i = 0; i < 32; i++) {
    challenge[i] = random(0, 256);
  } 
  //2. firmo la challenge
  if (!atecc.createSignature(challenge, 1)) {
    return false;
  } else {
    for (int i = 0; i < 64; i++){
      signature[i] = atecc.signature[i];
    }
  }

  //3. recupero la chiave pubblica
  if (!atecc.generatePublicKey(1, true)) return false;

  //4- verifica signature
  if (!atecc.verifySignature(challenge, atecc.signature, atecc.publicKey64Bytes)) return false;

  return true;
}

bool isAuthorized(){
  if (!atecc.generatePublicKey(1, true)) return false;

  for (int i = 0; i < 64; i++) {
    publicKey[i] = atecc.publicKey64Bytes[i];
  }

  if (memcmp(publicKey, authorizedKey, 64) == 0) return true;
  else return false;

}

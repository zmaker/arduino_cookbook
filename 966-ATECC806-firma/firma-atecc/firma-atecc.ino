#include <SparkFun_ATECCX08a_Arduino_Library.h> //Click here to get the library: http://librarymanager/All#SparkFun_ATECCX08a
#include <Wire.h>

ATECCX08A atecc;

uint8_t msg[32] = {
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
  0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
};

void setup() {
  //Wire.begin(); Arduino
  //ESP32
  Wire.begin(21, 22);
  Wire.setClock(10000);
  delay(1000);

  Serial.begin(115200);
  Serial.println("FIRMA ATECC");

  if (!atecc.begin()) {
    Serial.println("errore i2c?");
    while(1);
  }
  printInfo();

  if (!(atecc.configLockStatus && atecc.dataOTPLockStatus && atecc.slot0LockStatus) ) {
    Serial.println("atecc non configurato");
    while(1);
  }

  atecc.createSignature(msg);
  char buf[10];
  for (int i = 0; i < 64; i++) {
    sprintf(buf, "%02X, ", atecc.signature[i]);
    Serial.print(buf);
  }

    
}

void loop() {
  // put your main code here, to run repeatedly:

}

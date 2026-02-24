#include <SparkFun_ATECCX08a_Arduino_Library.h>
#include <Wire.h>

ATECCX08A atecc;

void setup() {
  //Wire.begin(); //arduino
  //esp32
  Wire.begin(21, 22);
  Wire.setClock(10000);
  delay(1000);

  Serial.begin(115200);
  Serial.println("Random ATECC806");

  if (!atecc.begin()) {
    Serial.println("errore i2c");
    while(1);
  }

  //atecc.random(10, 30);

  Serial.println("Seq 32 bytes");
  atecc.updateRandom32Bytes();
  char buf[10];
  for (int i = 0; i < 32; i++) {
    sprintf(buf, "%02X ", atecc.random32Bytes[i]);
    Serial.print(buf);
  }
  Serial.println("\n-------------------");
}

void loop() {
  long n = atecc.random(100);
  Serial.print(n);
  Serial.print(" ");
  delay(1000);
}

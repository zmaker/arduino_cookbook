// slave i2c
#include <Wire.h>

#define I2C_ADDR 0x7B

union databuff {
  float tc[5];
  uint8_t buff[20];
} dati;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  delay(2000);
  Serial.println("master");

}

void loop() {
  //invio un comando
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(0x01);
  Wire.endTransmission();

  //ricezione dati
  int nb = Wire.requestFrom(I2C_ADDR, 20);
  //if (nb == 20) {
    int i = 0;
    while(Wire.available()) {
      char c = Wire.read();
      dati.buff[i] = (uint8_t)c;
      i++;
    }
  //}
  Serial.println(dati.tc[0]);
  Serial.println(dati.tc[1]);
  delay(3000);
}




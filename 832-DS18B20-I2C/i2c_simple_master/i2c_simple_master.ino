#include <Wire.h>

//indirizzo 123 decimale del sensore da leggere
#define I2C_ADDR 0x7B

union databuff {
  float tc[5];
  uint8_t buff[20];
} dati;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  delay(3000);
  Serial.println("master");
}

void loop() {
  //se necessario mando un comando  
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(0x01);  
  Wire.endTransmission();  

  Wire.requestFrom(I2C_ADDR, 20);  
  int i = 0;
  while (Wire.available()){
    char c = Wire.read();
    dati.buff[i] = (uint8_t)c;
    i++;    
  }  
  Serial.print("t1:");
  Serial.print(dati.tc[0]);
  Serial.print(" t2:");
  Serial.println(dati.tc[1]);

  delay(2000);
}
#include <SimpleDHT.h>

// for DHT11,
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2

#define DHTPIN 2
SimpleDHT11 dht11;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("=================================");
  Serial.println("Sample DHT11...");

  byte temp = 0;
  byte umid = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(DHTPIN, &temp, &umid, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err=");
    Serial.println(err);
    delay(1000);
    return;
  }

  Serial.print("Sample OK: ");
  Serial.print((int)temp); Serial.print(" *C, ");
  Serial.print((int)umid); Serial.println(" H");

  // DHT11 sampling rate is 1HZ.
  delay(1500);
}

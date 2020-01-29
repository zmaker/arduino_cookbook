#include <SimpleDHT.h>

// for DHT22, 
//      VCC: 5V or 3V
SimpleDHT22 dht22(9);

void setup() {
  Serial.begin(9600);
}

void loop() {
  float temperature = 0;
  float humidity = 0; 
  dht22.read2(&temperature, &humidity, NULL);
  Serial.print((float)temperature); Serial.print(" *C, ");
  Serial.print((float)humidity); Serial.println(" RH%");
  
  // DHT22 sampling rate is 0.5HZ.
  delay(1000);
  byte tt = 0;
  byte hh = 0; 
  dht22.read(&tt, &hh, NULL);
  Serial.print(tt); Serial.print(" *C, ");
  Serial.print(hh); Serial.println(" RH%");
  
  delay(1000);
}

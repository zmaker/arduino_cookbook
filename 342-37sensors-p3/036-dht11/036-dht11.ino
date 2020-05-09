/*
  036 - DHT11
*/
#include <SimpleDHT.h>

int pinDHT11 = 2;
SimpleDHT11 dht11(pinDHT11);

void setup() {
  Serial.begin(9600);
}

void loop() {
  byte temperature = 0;
  byte humidity = 0;

  dht11.read(&temperature, &humidity, NULL);
  Serial.print((int)temperature); Serial.print(" C, "); 
  Serial.print((int)humidity); Serial.println(" %");
  
  delay(2500);
}

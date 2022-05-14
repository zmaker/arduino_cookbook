// program to test POT on the IoT Proto Shield Plus
// www.gtronicsShop.com

// select ARDUINO NANO or EVERY according to the device your are using
// tools->Board->"ARDUINO NANO xxxx"
// select port number


#define ANALOG_IN_PIN A6  // Analog input pin that the potentiometer is attached to


int adcValue = 0;        // value read from the pot

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  adcValue = analogRead(ANALOG_IN_PIN);

  // print the results to the Serial Monitor:
  Serial.print("adcValue = ");
  Serial.println(adcValue);

  // wait 100 milliseconds before the next loop for the analog-to-digital
  delay(100);
}

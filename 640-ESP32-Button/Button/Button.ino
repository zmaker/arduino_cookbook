/*
 * scheda: DOIT ESP32 dev kit
 * AZDelivery - https://amzn.to/3GwypiZ
 * Fare UPLOAD e poi premere il tasto RST sulla scheda
 * 
 * URL per config schede: https://dl.espressif.com/dl/package_esp32_index.json
 * 
 * un led sul pin 2 e un bt con pullup sul pin 4
 * 
 */
void setup() {
  pinMode(2, OUTPUT);
  pinMode(4, INPUT);
}
 
void loop() {  
  digitalWrite(2, digitalRead(4));  
}

/*
 * scheda: DOIT ESP32 dev kit
 * AZDelivery - https://amzn.to/3GwypiZ
 * Fare UPLOAD e poi premere il tasto RST sulla scheda
 * 
 * URL per config schede: https://dl.espressif.com/dl/package_esp32_index.json
 * 
 * Blink con led sul pin 2
 * 
 */
void setup() {
  pinMode(2, OUTPUT);
}
 
void loop() {
  
  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  delay(500);
  
}

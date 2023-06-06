/** Blink
https://docs.arduino.cc/hardware/opta
*/
void setup() {
  pinMode(LED_D0, OUTPUT);  
}

void loop() {
  digitalWrite(LED_D0, HIGH);
  delay(100);
  digitalWrite(LED_D0, LOW);
  delay(100);
}
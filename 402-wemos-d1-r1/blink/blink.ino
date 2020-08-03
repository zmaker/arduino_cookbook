/*
 * http://arduino.esp8266.com/stable/package_esp8266com_index.json
 */

void setup() {
  pinMode(16, OUTPUT);
}

void loop() {
  digitalWrite(16, HIGH);
  delay(100);
  digitalWrite(16, LOW);
  delay(100);
}

// http://arduino.esp8266.com/stable/package_esp8266com_index.json
// http://arduino.esp8266.com/versions/2.5.0/package_esp8266com_index.json


int led = 2;
void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
  delay(100);
}

//int pin = 14; //A0
int pin = 19; //A5

void setup() {
  pinMode(pin, OUTPUT);

}

void loop() {
  digitalWrite(pin, HIGH);
  delay(500);
  digitalWrite(pin, LOW);
  delay(500);
}

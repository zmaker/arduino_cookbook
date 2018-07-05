int pin = 7;

void setup() {
  pinMode(pin, OUTPUT);

}

void loop() {
  int nota = random(200, 1000);
  tone(pin, nota, 100);
  delay(100);
}

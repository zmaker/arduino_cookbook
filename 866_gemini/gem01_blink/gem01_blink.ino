void setup() {
  // Imposta il pin 13 come uscita digitale
  pinMode(13, OUTPUT);
}

void loop() {
  // Accendi il LED
  digitalWrite(13, HIGH);
  // Aspetta un secondo
  delay(1000);
  // Spegni il LED
  digitalWrite(13, LOW);
  // Aspetta un secondo
  delay(1000);
}
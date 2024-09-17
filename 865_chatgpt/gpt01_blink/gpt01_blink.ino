// Imposta il pin 13 per il LED
int ledPin = 13;

void setup() {
  // Imposta il pin 13 come output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Accendi il LED
  digitalWrite(ledPin, HIGH);
  // Attendi un secondo (1000 millisecondi)
  delay(1000);
  // Spegni il LED
  digitalWrite(ledPin, LOW);
  // Attendi un altro secondo
  delay(1000);
}

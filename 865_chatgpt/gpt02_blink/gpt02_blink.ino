// Imposta il pin 13 per il LED
int ledPin = 13;

void setup() {
  // Imposta il pin 13 come output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Accendi il LED per 200ms
  digitalWrite(ledPin, HIGH);
  delay(200); // Pausa di 200ms
  
  // Spegni il LED per 800ms
  digitalWrite(ledPin, LOW);
  delay(800); // Pausa di 800ms
}

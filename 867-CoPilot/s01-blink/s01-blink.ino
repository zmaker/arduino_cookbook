void setup() {
  pinMode(13, OUTPUT); // Imposta il pin 13 come uscita
}

void loop() {
  digitalWrite(13, HIGH); // Accendi il LED
  delay(500); // Aspetta per 500 millisecondi
  digitalWrite(13, LOW); // Spegni il LED
  delay(500); // Aspetta per 500 millisecondi
}

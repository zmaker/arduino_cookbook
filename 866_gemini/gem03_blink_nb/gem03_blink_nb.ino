const long interval = 500;  // Intervallo di lampeggiamento in millisecondi
unsigned long previousMillis = 0;

void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // salva il momento attuale
    previousMillis = currentMillis;

    // cambia lo stato del LED
    digitalWrite(13, !digitalRead(13));
  }
}
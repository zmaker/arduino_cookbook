unsigned long previousMillis = 0; // Variabile per memorizzare l'ultimo aggiornamento
const long interval = 500; // Intervallo di tempo in millisecondi

void setup() {
  pinMode(13, OUTPUT); // Imposta il pin 13 come uscita
}

void loop() {
  unsigned long currentMillis = millis(); // Ottieni il tempo corrente

  if (currentMillis - previousMillis >= interval) { // Controlla se l'intervallo è passato
    previousMillis = currentMillis; // Aggiorna il tempo dell'ultimo aggiornamento

    // Se il LED è acceso, spegnilo; altrimenti, accendilo
    if (digitalRead(13) == HIGH) {
      digitalWrite(13, LOW);
    } else {
      digitalWrite(13, HIGH);
    }
  }
}

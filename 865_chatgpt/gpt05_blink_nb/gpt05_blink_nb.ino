// Definizione dei pin e delle variabili
int ledPin = 13;  // Pin collegato al LED
unsigned long previousMillis = 0;  // Tempo dell'ultimo cambiamento di stato
const long interval = 1000;  // Intervallo di lampeggio (1 secondo)

void setup() {
  // Imposta il pin del LED come output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Ottiene il tempo corrente
  unsigned long currentMillis = millis();
  
  // Controlla se è trascorso l'intervallo
  if (currentMillis - previousMillis >= interval) {
    // Salva il momento dell'ultimo cambiamento
    previousMillis = currentMillis;

    // Cambia lo stato del LED
    if (digitalRead(ledPin) == LOW) {
      digitalWrite(ledPin, HIGH);  // Accendi il LED
    } else {
      digitalWrite(ledPin, LOW);   // Spegni il LED
    }
  }
}

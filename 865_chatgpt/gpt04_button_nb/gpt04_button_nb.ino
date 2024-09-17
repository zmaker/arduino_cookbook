// Definizione dei pin
int ledPin13 = 13;  // LED sul pin 13
int ledPin12 = 12;  // LED sul pin 12
int buttonPin = 2;  // Pulsante sul pin 2
int buttonState = 0; // Variabile per memorizzare lo stato del pulsante

unsigned long previousMillis = 0; // Tempo dell'ultimo cambiamento di stato del LED sul pin 13
const long interval = 500; // Intervallo di lampeggiamento (500ms acceso, 500ms spento)

void setup() {
  // Imposta i pin dei LED come output
  pinMode(ledPin13, OUTPUT);
  pinMode(ledPin12, OUTPUT);
  
  // Imposta il pin del pulsante come input
  pinMode(buttonPin, INPUT);
}

void loop() {
  // Ottenere il tempo corrente
  unsigned long currentMillis = millis();
  
  // Controllare se è il momento di cambiare lo stato del LED sul pin 13
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Aggiorna il tempo dell'ultimo cambiamento

    // Cambia lo stato del LED sul pin 13
    if (digitalRead(ledPin13) == LOW) {
      digitalWrite(ledPin13, HIGH); // Accendi il LED
    } else {
      digitalWrite(ledPin13, LOW);  // Spegni il LED
    }
  }

  // Legge lo stato del pulsante
  buttonState = digitalRead(buttonPin);

  // Se il pulsante viene premuto, accendi il LED sul pin 12
  if (buttonState == HIGH) {
    digitalWrite(ledPin12, HIGH);  // Accendi il LED
  } else {
    // Se il pulsante non è premuto, spegni il LED sul pin 12
    digitalWrite(ledPin12, LOW);   // Spegni il LED
  }
}

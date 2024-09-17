// Definizione dei pin e delle variabili
int ledPin = 6;         // Pin collegato al LED
int buttonPin = 2;      // Pin collegato al pulsante
int buttonState = 0;    // Variabile per memorizzare lo stato corrente del pulsante
int lastButtonState = 0; // Variabile per memorizzare lo stato precedente del pulsante
int ledState = 0;       // Stato del LED (0 = spento, 1 = 50%, 2 = 100%)

void setup() {
  // Imposta il pin del LED come output
  pinMode(ledPin, OUTPUT);
  // Imposta il pin del pulsante come input
  pinMode(buttonPin, INPUT);
}

void loop() {
  // Legge lo stato corrente del pulsante
  buttonState = digitalRead(buttonPin);
  
  // Verifica se c'è un cambiamento nello stato del pulsante (pressione)
  if (buttonState == HIGH && lastButtonState == LOW) {
    // Ogni volta che il pulsante viene premuto, cambia lo stato del LED
    ledState++;
    
    // Cicla gli stati (0 = spento, 1 = 50%, 2 = 100%)
    if (ledState > 2) {
      ledState = 0;
    }

    // Cambia la luminosità del LED in base allo stato
    if (ledState == 0) {
      analogWrite(ledPin, 0);       // Spegni il LED
    } else if (ledState == 1) {
      analogWrite(ledPin, 128);     // Accendi il LED al 50% (128 su 255)
    } else if (ledState == 2) {
      analogWrite(ledPin, 255);     // Accendi il LED al 100% (255 su 255)
    }
  }

  // Salva lo stato corrente del pulsante per il prossimo ciclo
  lastButtonState = buttonState;
}

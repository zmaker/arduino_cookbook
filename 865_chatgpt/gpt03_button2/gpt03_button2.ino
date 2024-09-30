// Definizione dei pin
int ledPin13 = 13;  // LED sul pin 13
int ledPin12 = 12;  // LED sul pin 12
int buttonPin = 2;  // Pulsante sul pin 2
int buttonState = 0; // Variabile per memorizzare lo stato del pulsante
int led12State = LOW; // Stato del LED sul pin 12, inizialmente spento

void setup() {
  // Imposta i pin dei LED come output
  pinMode(ledPin13, OUTPUT);
  pinMode(ledPin12, OUTPUT);
  
  // Imposta il pin del pulsante come input
  pinMode(buttonPin, INPUT);
}

void loop() {
  // Far lampeggiare il LED sul pin 13
  digitalWrite(ledPin13, HIGH);
  delay(500); // LED acceso per 500ms
  digitalWrite(ledPin13, LOW);
  delay(500); // LED spento per 500ms

  // Legge lo stato del pulsante
  buttonState = digitalRead(buttonPin);
  
  // Se il pulsante viene premuto, accendi il LED sul pin 12 e mantienilo acceso
  if (buttonState == HIGH) {
    led12State = HIGH;
  }

  // Imposta lo stato del LED sul pin 12
  digitalWrite(ledPin12, led12State);
}

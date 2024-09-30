const int ledPin1 = 13;  // Pin del primo LED
const int ledPin2 = 12;  // Pin del secondo LED
const int buttonPin = 2;  // Pin del pulsante

const long interval = 500;  // Intervallo di lampeggiamento in millisecondi

unsigned long previousMillis = 0;
int buttonState = 0;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(buttonPin, INPUT); // Impostiamo il pin del pulsante come ingresso
//  digitalWrite(buttonPin, LOW); // Attiviamo la resistenza interna di pull-down
}

void loop() {
  unsigned long currentMillis = millis();

  // Leggiamo lo stato del pulsante
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    // Pulsante premuto, accendiamo il LED sul pin 12
    digitalWrite(ledPin2, HIGH);
  } else {
    // Pulsante non premuto, spegniamo il LED sul pin 12
    digitalWrite(ledPin2, LOW);
  }

  // Lampeggiamento del LED sul pin 13
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    digitalWrite(ledPin1, !digitalRead(ledPin1));
  }
}
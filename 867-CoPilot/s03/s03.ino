const int ledPin13 = 13;
const int ledPin12 = 12;
const int buttonPin = 2;

unsigned long previousMillis = 0;
const long interval = 500;

void setup() {
  pinMode(ledPin13, OUTPUT);
  pinMode(ledPin12, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  // Far lampeggiare il LED sul pin 13
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (digitalRead(ledPin13) == HIGH) {
      digitalWrite(ledPin13, LOW);
    } else {
      digitalWrite(ledPin13, HIGH);
    }
  }

  // Controllare lo stato del pulsante
  if (digitalRead(buttonPin) == HIGH) {
    digitalWrite(ledPin12, HIGH);
  } else {
    digitalWrite(ledPin12, LOW);
  }
}

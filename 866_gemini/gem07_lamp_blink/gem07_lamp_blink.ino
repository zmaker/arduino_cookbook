const int ledPin = 6;
const int buttonPin = 2;

int brightness = 0;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;
int previousReading = 0;
int buttonState = LOW;

// Variabili per il lampeggiamento
const int blinkInterval = 500;  // Intervallo di lampeggiamento in millisecondi
unsigned long previousMillis = 0;
bool blinkingState = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, LOW);
}

void loop() {
  int reading = digitalRead(buttonPin);
  if (reading != previousReading) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        brightness++;
        if (brightness > 3) {
          brightness = 0;
          blinkingState = true;
        }
      }
    }
  }
  previousReading = reading;

  unsigned long currentMillis = millis();

  if (blinkingState && (currentMillis - previousMillis >= blinkInterval)) {
    previousMillis = currentMillis;
    digitalWrite(ledPin, !digitalRead(ledPin));
  } else if (!blinkingState) {
    analogWrite(ledPin, brightness * 51);
  }
}
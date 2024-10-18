const int ledPin = 6;
const int buttonPin = 2;

int buttonState = 0;
int lastButtonState = 0;
int brightness = 0;
int pressCount = 0;
unsigned long previousMillis = 0;
const long interval = 500; // Intervallo di lampeggiamento

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // Se il pulsante è premuto
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      pressCount++;
      if (pressCount > 4) {
        pressCount = 1;
      }

      switch(pressCount) {
        case 1:
          brightness = 127; // 50%
          analogWrite(ledPin, brightness);
          break;
        case 2:
          brightness = 255; // 100%
          analogWrite(ledPin, brightness);
          break;
        case 3:
          // Lampeggiamento gestito nel loop principale
          break;
        case 4:
          brightness = 0; // Off
          analogWrite(ledPin, brightness);
          break;
      }
    }
    
    // De-bouncing del pulsante
    delay(50);
  }

  lastButtonState = buttonState;

  // Stato di lampeggiamento del LED
  if (pressCount == 3) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      if (digitalRead(ledPin) == HIGH) {
        digitalWrite(ledPin, LOW);
      } else {
        digitalWrite(ledPin, HIGH);
      }
    }
  }
}

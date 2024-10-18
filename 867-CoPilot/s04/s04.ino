const int ledPin = 6;
const int buttonPin = 2;

int buttonState = 0;
int lastButtonState = 0;
int brightness = 0;
int pressCount = 0;

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
      if (pressCount > 3) {
        pressCount = 1;
      }
      
      switch(pressCount) {
        case 1:
          brightness = 127; // 50%
          break;
        case 2:
          brightness = 255; // 100%
          break;
        case 3:
          brightness = 0; // off
          break;
      }

      analogWrite(ledPin, brightness);
    }

    // De-bouncing del pulsante
    delay(50);
  }

  lastButtonState = buttonState;
}

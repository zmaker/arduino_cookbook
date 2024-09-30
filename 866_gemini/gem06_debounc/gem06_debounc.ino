const int ledPin = 6;
const int buttonPin = 2;
int buttonState = 0;

int brightness = 0;
unsigned long lastDebounceTime = 0;  // Variabile per memorizzare il tempo dell'ultimo cambiamento di stato
const unsigned long debounceDelay = 50;  // Tempo di debouncing in millisecondi
int previousReading = 0;  // Variabile per memorizzare lo stato precedente del pulsante

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);  // Impostiamo il pin del pulsante come ingresso
  digitalWrite(buttonPin, LOW);  // Attiviamo la resistenza interna di pull-down
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
        if (brightness > 2) {
          brightness = 0;
        }
        analogWrite(ledPin, brightness * 51);
      }
    }
  }
  previousReading = reading;
}
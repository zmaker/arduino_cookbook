const int ledPin = 6;  // Pin a cui è collegato il LED
const int buttonPin = 2;  // Pin a cui è collegato il pulsante

int brightness = 0;  // Variabile per controllare la luminosità del LED

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);  // Impostiamo il pin del pulsante come ingresso
  digitalWrite(buttonPin, LOW);  // Attiviamo la resistenza interna di pull-down
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    brightness++;
    if (brightness > 2) {
      brightness = 0;
    }
    analogWrite(ledPin, brightness * 51);  // Imposta la luminosità del LED
  }
}
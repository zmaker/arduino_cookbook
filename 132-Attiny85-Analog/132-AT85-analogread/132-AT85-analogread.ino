//AT85
//clock internal 8MhZ

//legge un trimmer colelgato sul pin 3 (A3) (fisico n.2)
//comanda PWM su pin 0 (fisico n.5)

void setup() {
  pinMode(0, OUTPUT);  
}

void loop() {
  int val = analogRead(A3);
  val = map(val, 0, 1023, 0, 255);
  analogWrite(0, val);
  delay(100);
}

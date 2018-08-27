void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  char comando = Serial.read();
  if (comando == 'a') {
    digitalWrite(13, HIGH);  
  }
  if (comando == 's') {
    digitalWrite(13, LOW);  
  }
}

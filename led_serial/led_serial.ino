char comando;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  comando = Serial.read();
  if (comando == 'a') {
    digitalWrite (13, HIGH);
    Serial.println ("Acceso");
  }
  if (comando == 's') {
    digitalWrite (13, LOW);
    Serial.println ("Spento");
  }
}

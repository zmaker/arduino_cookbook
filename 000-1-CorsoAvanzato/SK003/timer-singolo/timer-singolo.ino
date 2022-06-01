unsigned long t1;
bool ATTIVO = false;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  t1 = millis();
}

void loop() {  
  if ( ((millis() - t1) > 3000) && !ATTIVO) {
    digitalWrite(2, HIGH);
    Serial.println("OK");
    ATTIVO = true;
  }  
}

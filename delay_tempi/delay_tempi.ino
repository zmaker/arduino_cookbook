long t1 = 0;
long pausa = 5*1000;

void setup() {
  Serial.begin(9600);
  t1 = millis();
  Serial.println("inizio pausa");  
}

void loop() {
  long diff = millis() - t1;
  if (diff > pausa) {
    Serial.println("fine pausa lunga");      
  }
}

int stato = LOW;
unsigned long t1;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  if (digitalRead(2) && ( (millis()-t1) > 300) ) {
    t1 = millis();
    stato = !stato;
    digitalWrite(3, stato);    
  }

}

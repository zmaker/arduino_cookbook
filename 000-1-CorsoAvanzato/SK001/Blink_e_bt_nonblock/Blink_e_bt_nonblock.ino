unsigned long t1;
int led = LOW;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, INPUT);
  t1 = millis(); //12:01
}

void loop() {
  if ((millis() - t1) >= 500) {
    led = !led;
    digitalWrite(2, led);
    t1 = millis();
  }
  
  if (digitalRead(3)) {
    digitalWrite(4, HIGH);  
  } else {
    digitalWrite(4, LOW);  
  }
}

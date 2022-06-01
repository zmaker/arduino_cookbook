unsigned long t1, t2;
int led = LOW;

void setup () {
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  t1 = millis();
}

void loop () {

  if ((millis() - t1) > 1000) {
    led = !led;
    digitalWrite(3, led);
    t1 = millis();
  }
  
  if (digitalRead(2)) {
    digitalWrite(4, HIGH);
  } else {
    digitalWrite(4, LOW);
  }
 
}

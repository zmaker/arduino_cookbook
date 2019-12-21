void setup() {
  pinMode(13, OUTPUT);
}

unsigned long t1, dt;
int LED = LOW;

void loop() {
  dt = millis() - t1;
  if (dt >= 500) {
    t1 = millis();
    LED = !LED;
    digitalWrite(13, LED);
  }
  
}

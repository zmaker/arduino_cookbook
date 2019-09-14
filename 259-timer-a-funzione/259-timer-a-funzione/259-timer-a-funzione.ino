
void setup() {
  Serial.begin(9600);
  Serial.println("timer");
}

void loop() {
  if (mytimer(1000)) {
    Serial.println("ok");
  }    
}

int mytimer (int timer1) {
  static unsigned long t1, dt;
  int ret = 0;
  dt = millis() - t1;
  if (dt >= 1000) {
      t1 = millis();
      ret = 1;
  }
  return ret;
}

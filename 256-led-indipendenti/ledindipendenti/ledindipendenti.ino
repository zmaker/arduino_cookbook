unsigned long t1, dt1;
unsigned long t2, dt2;

int tled1 = 600;
int tled2 = 350;

int st1 = LOW;
int st2 = LOW;

void setup() {
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  dt1 = millis() - t1;
  if (dt1 > tled1) {
    st1 = !st1;
    digitalWrite(12, st1);
    t1 = millis();
  }


  dt2 = millis() - t2;
  if (dt2 > tled2) {
    st2 = !st2;
    digitalWrite(13, st2);
    t2 = millis();
  }
  
}

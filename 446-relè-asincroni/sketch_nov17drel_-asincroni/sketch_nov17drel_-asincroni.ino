int prog[3] = {1000, 3000, 4000};
int timer[3] = {0,0,0};

unsigned long t1, dt;

void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  t1 = millis();
}

void loop() {
  dt = millis() - t1;
  if (dt > 10) {      
      if (timer[0] > 0) {
        timer[0] = timer[0] - 10;
      }
      if (timer[1] > 0) {
        timer[1] = timer[1] - 10;
      }
      if (timer[2] > 0) {
        timer[2] = timer[2] - 10;
      }
      t1 = millis();
  }

  if (digitalRead(2) && (timer[0] == 0)) {
    timer[0] = prog[0];
    digitalWrite(13, HIGH);
  }
  if (digitalRead(3) && (timer[1] == 0)) {
    timer[1] = prog[1];
    digitalWrite(12, HIGH);
  }
  if (digitalRead(4) && (timer[2] == 0)) {
    timer[2] = prog[2];
    digitalWrite(11, HIGH);
  }

  if (timer[0] == 0) {
    digitalWrite(13, LOW);
  }
  if (timer[1] == 0) {
    digitalWrite(12, LOW);
  }
  if (timer[2] == 0) {
    digitalWrite(11, LOW);
  }
}

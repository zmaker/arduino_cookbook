void setup() {
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
  Serial.begin(9600);
}

unsigned long t1, dt;
bool RUN = false;

void loop() {
  dt = millis() - t1;
  if ((dt >= 3000) && RUN) {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    RUN = false;
  }
  
  //verifica innesco task
  if (digitalRead(2)) {
    t1 = millis();
    delay(300);
    RUN = true;
  }
}

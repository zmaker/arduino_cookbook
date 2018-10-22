#define INTERVALLO 1000

int stato = LOW;
unsigned long t0, dt;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(4, INPUT);
  pinMode(2, OUTPUT);

  t0 = millis();
}

void loop() {
  dt = millis() - t0;
  if (dt >= INTERVALLO) {
    t0 = millis();
    stato = !stato;
    digitalWrite(13, stato);
  }

  if (digitalRead(4)) {
    digitalWrite(2, HIGH);  
  } else {
    digitalWrite(2, LOW);  
  }
  
}



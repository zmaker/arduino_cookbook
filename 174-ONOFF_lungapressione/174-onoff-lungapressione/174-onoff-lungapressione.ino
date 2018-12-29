void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT);
  pinMode(2, OUTPUT);
}

bool tasto;
bool prev_tasto;
unsigned long t0;
int stato = LOW;

void loop() {
  tasto = digitalRead(8);

  if (!prev_tasto && tasto) {
    Serial.println("inizio conteggio");
    t0 = millis();
  }

  if (prev_tasto && !tasto){
    Serial.println("fine conteggio");
    unsigned long t = millis() - t0;
    Serial.print("t press:");
    Serial.println(t);

    if (t > 1500) {
      stato = !stato;
      digitalWrite(2, stato);
    }
    
  }

  prev_tasto = tasto;
}





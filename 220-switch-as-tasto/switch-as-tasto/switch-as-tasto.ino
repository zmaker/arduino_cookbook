void setup() {
  Serial.begin(9600);
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);
}

bool tasto;
bool prev_tasto;

void loop() {  
  tasto = digitalRead(12);

  if (!prev_tasto && tasto) {
    Serial.println("off-on - salita");
    prev_tasto = tasto;
  }
  
  if (prev_tasto && !tasto) {
    Serial.println("on-off - discesa");
    prev_tasto = tasto;
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    
  }
  
}

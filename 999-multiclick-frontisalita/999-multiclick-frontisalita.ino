void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT);
}

bool tasto;
bool prev_tasto;

void loop() {  
  tasto = digitalRead(8);

  if (!prev_tasto && tasto) {
    Serial.println("off-on - salita");
    prev_tasto = tasto;
  }
  
  if (prev_tasto && !tasto) {
    Serial.println("on-off - discesa");
    prev_tasto = tasto;
  }
  
}

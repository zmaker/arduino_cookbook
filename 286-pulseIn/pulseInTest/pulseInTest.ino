
void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
}

void loop() {
  unsigned long t = pulseIn(2, HIGH, 3000000);
  if (t == 0) {
    Serial.println("tempo scaduto");
  } else {
    Serial.print("hai premuto per: ");
    Serial.println(t); 
  }
}

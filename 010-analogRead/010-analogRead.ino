void setup() {
  pinMode(13, OUTPUT);
  pinMode(7, INPUT);
  Serial.begin(9600);
}

void loop() {  
  int v = analogRead(A0);

  Serial.println(v);
  if (v < 900) {
    digitalWrite(13, HIGH);  
  } else {
    digitalWrite(13, LOW);  
  }  
  delay(200);
}

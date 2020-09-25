int statoled = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  int val = analogRead(A0);
  Serial.println(val);

  if (val >= 100) {
    statoled = !statoled;
    digitalWrite(13, statoled);
    Serial.println("toc toc");
    delay(200);  
  }

  delay(10);
}

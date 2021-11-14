int toll = 5;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int v = analogRead(A0);
  
  if (v < toll) {
    Serial.println("0");
  } else if ((v > 320-toll) && (v < 320+toll)) {
    Serial.println("1");
  } else if ((v > 512-toll) && (v < 512+toll)) {
    Serial.println("2");
  } else {
    Serial.println("?");
  }
  
  //Serial.println(v);
  delay(100);
}

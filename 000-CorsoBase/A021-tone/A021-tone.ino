void setup () {
  randomSeed(analogRead(A0));
}

void loop () {
  //int n = analogRead(A0);
  
  tone(8, random(100, 1000), 100);
  delay(150);
}

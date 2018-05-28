void setup() {
  // put your setup code here, to run once:
 pinMode(5, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 
  int f = random(100, 1000);
  int t = random(100, 500);
  tone(5, f, t);
  int d = random(50, 150);
  delay(d);
}

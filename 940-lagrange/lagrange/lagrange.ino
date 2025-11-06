// Polinomio interpolante per (0,50),(30,200),(70,80),(100,220)
// P(x) = 0.002238095238*x^3 - 0.338095238095*x^2 + 13.128571428571*x + 50

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
}

void loop() {
  for (int x = 0; x <= 100; x++){
    float y = 0.002238095238f*x*x*x - 0.338095238095f*x*x + 13.128571428571f*x + 50.0f;
    y = constrain(y, 0, 255);
    analogWrite(9, y);
    Serial.print(x);
    Serial.print("\t");
    Serial.println(y);
    delay(50);
  }
  delay(5000);
}

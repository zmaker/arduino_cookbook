int c = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello Arduino");
}

void loop() {
  Serial.print("Valore di c: ");Serial.println(c);
  delay(1000);
  c++;
}

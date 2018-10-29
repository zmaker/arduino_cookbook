void setup() {
  Serial.begin(9600);
}

void loop() {
  int n = fnz();
  delay(1000);
  Serial.println(n);
}

int fnz() {
  int static counter = 0;
  counter++;
  return counter;  
}

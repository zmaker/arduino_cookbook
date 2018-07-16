int i = 100;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(i);
  i++;
  delay(1000);
}

void setup() {
  Serial.begin(9600);
}

int n = 0;

void loop() {
  Serial.println(n);
  Serial.println('\n');
  delay(1000);
  n++;    
}

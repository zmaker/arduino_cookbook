void setup() {
  Serial.begin(9600);
}

int n = 0;

void loop() {
  Serial.print(n);
  Serial.println('\n');
  delay(1000);
  n++;    
}


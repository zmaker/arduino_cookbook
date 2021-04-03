void setup() {
  Serial.begin(9600);
  for (int i = 2; i <= 9; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);  
  }
  digitalWrite(6, HIGH); 
  digitalWrite(7, HIGH); 
  digitalWrite(8, HIGH); 
  digitalWrite(9, LOW); 
}

int c = 0;
unsigned long dt, t1;

void loop() {
  displayDigit(0, (c%10));
  delay(2);
  displayDigit(1, ((c/10)%10));
  delay(2);
  displayDigit(2, ((c/100)%10));
  delay(2);
  displayDigit(3, ((c/1000)%10));
  delay(2);
  
  dt = millis() - t1;
  if (dt >= 200) {
    c++;
    t1 = millis();
    
  } 
}

void displayDigit(int d, int n) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(9-i, (i == d? LOW : HIGH));     
  }
  digitalWrite(5, (n & B00000001));
  digitalWrite(4, (n & B00000010));
  digitalWrite(3, (n & B00000100));
  digitalWrite(2, (n & B00001000));    
}

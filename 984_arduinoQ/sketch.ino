int c = 0;

void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(9600);  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2, !digitalRead(2));
  Serial.println(c)++;
  delay(1000);
}



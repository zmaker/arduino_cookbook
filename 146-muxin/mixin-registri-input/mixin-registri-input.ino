volatile int stato = LOW;

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(3), readin, RISING);
  pinMode(8, INPUT); 
  pinMode(9, INPUT); 
  pinMode(10, INPUT); 
  pinMode(11, INPUT); 
  pinMode(12, INPUT);   
  Serial.println("ok");
}

void loop() {
  stato = HIGH;
  if (stato) {
    
    int a = digitalRead(8);
    int b = digitalRead(9);
    int c = digitalRead(10);
    int d = digitalRead(11);
    int e = digitalRead(12);    
    Serial.print(a);
    Serial.print(b);
    Serial.print(c);
    Serial.print(d);
    Serial.println(e);        
    //stato = LOW;
  }  
  delay(100);
}

void readin() {
  stato = HIGH;  
}

int stato;

void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

unsigned long t1;

void loop() {
  switch(stato) {
    case 0:
      st0();
      t1 = millis();
      break;   
    case 1:
      waitAndGo(2);
      break;
    case 2:
      blink(10, 3);
      break;   
    case 3:
      st1();
      t1 = millis();
      break;   
    case 4:
      waitAndGo(5);
      break;
    case 5:
      blink(12, 0);
      break; 
  }
}

void st0(){
  Serial.println("0");
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  stato = 1;
}

void waitAndGo(int next) {
  Serial.print(".");
  if ((millis() - t1) >= 3000) {
    t1 = millis();
    stato = next;  
    Serial.print("->");
    Serial.println(next);  
  }
}

void blink(int pin, int next){
  int led = LOW;
  Serial.print("blink - ");
  Serial.println(stato);
  for (int i = 0; i < 6; i++) {
    digitalWrite(pin, led);
    delay(500);
    led = !led;
  }
  Serial.print("->");
  Serial.println(next); 
  stato = next;   
}

void st1(){
  Serial.println("1");
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);  
  stato = 4; 
}

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

void setup() {
  Serial.begin(9600);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT); 
  pinMode(ENB, OUTPUT);
  analogWrite(ENB, 0);
  analogWrite(ENA, 0);
}

void loop() {
  //imposta direzione  
  Serial.println("run");
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  for (int i = 0; i <= 255; i++) {
    analogWrite(ENB, i);
    analogWrite(ENA, i);
    delay(10);
  }
  for (int i = 255; i >= 0; i--) {
    analogWrite(ENB, i);
    analogWrite(ENA, i);
    delay(10);
  }
}

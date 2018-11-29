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
  digitalWrite(ENB, HIGH);
  digitalWrite(ENA, HIGH);
}

void loop() {
  Serial.println("run");
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  delay(500); //delay 500ms
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW); 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);

  delay(500);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); //Right wheel turning backwards 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(500);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH); //Right wheel stoped
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  delay(500);
}

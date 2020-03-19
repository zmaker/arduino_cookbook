#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

void setup() {
  Serial.begin(9600);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
}

unsigned long r, g, b;

void loop() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  r = pulseIn(sensorOut, LOW);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  g = pulseIn(sensorOut, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  b = pulseIn(sensorOut, LOW);

  Serial.print("R=");
  Serial.print(r);
  Serial.print("\tG=");
  Serial.print(g);
  Serial.print("\tB=");
  Serial.println(b);

  delay(100);

  if ( (r <= 5) && (g <= 12) && (b <= 9) ) {
      Serial.println("RED");
      analogWrite(11, 255);
  } else if ( (r <= 9) && (g <= 10) && (b <= 6) ) {
      Serial.println("BLUE");
      analogWrite(9, 255);
  } else if ( (r <= 8) && (g <= 8) && (b <= 10) ) {
      Serial.println("GREEN");
      analogWrite(10, 255);
  } else {
    analogWrite(9, 0);
    analogWrite(10, 0);
    analogWrite(11, 0);
  }
}

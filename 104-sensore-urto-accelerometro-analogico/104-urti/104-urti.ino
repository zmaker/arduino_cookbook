void setup() {
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

int x, y, z;
int MAXV = 30;

void loop() {
  x = analogRead(A0);
  y = analogRead(A1);
  z = analogRead(A2);
  /*String str = "v: \t" + String(x) + 
    "\t" + String(y) + 
    "\t" + String(z);
  Serial.println(str);
  delay(100);
  */
  Serial.println(x); 
  if (x > MAXV/4) {
    digitalWrite(11, HIGH);
    Serial.print(".");
  }  
  if (x > MAXV/2) {
    digitalWrite(12, HIGH);
    Serial.print("o");
  }
  if (x > 3*MAXV/4) {
    digitalWrite(13, HIGH);
    Serial.print("O");
  }
  Serial.println(" ");
  delay(100);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}

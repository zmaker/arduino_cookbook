
void setup() {
  Serial.begin(9600);
}

int i = 0;
float a = 0.0; 

void loop() {
  a = ((float)map(i, 0, 100, 0, 628)) / 100.0;
  int pwm = 127 + (int)(sin(a) * 127.0);
  analogWrite(11, pwm);
  Serial.println(pwm);
  i++;
  if (i == 100) i = 0;
  delay(40);
}

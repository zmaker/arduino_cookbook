void setup() {
  Serial.begin(9600);
}

int i = 0;

void loop() {
  for (int i = 0; i <= 100; i++) {
    analogWrite(11, logpwm(i));
    analogWrite(6, map(i, 0, 100, 255, 0));
    delay(10);
  }
  for (int i = 100; i >= 0; i--) {
    analogWrite(11, logpwm(i));   
    analogWrite(6, map(i, 0, 100, 255, 0));
    delay(10);
  }  
}

int logpwm(int perc){
  int i = map(perc, 0, 100, 100, 272);
  float n = 1 - log(((float)i) / 100.0f) ;
  Serial.println(n);
  return (int)map(n*100, 0, 100, 0, 255);
}

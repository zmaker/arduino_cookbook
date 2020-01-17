int bt = 2;
int led = 13;

void setup() {
  Serial.begin(9600);
  pinMode(bt, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  int n = digitalRead(bt);
  digitalWrite(led, n);
  delay(10);
}

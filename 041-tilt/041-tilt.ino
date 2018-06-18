const int led = 13;

void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  int s = digitalRead(8);
  if (s) {
    digitalWrite(led, HIGH);
    Serial.println("on");
  } else {
    digitalWrite(led, LOW);
  }

}

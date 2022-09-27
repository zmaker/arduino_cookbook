void setup() {
  Serial.begin(9600);

}

int a = 0;
void loop() {
  Serial.println(a);
  a++;
  delay(1000);
}

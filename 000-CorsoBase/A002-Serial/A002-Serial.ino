int count = 0;

void setup() {
  Serial.begin(9600); //baud 115200
  Serial.println("Hello World!");
  Serial.println("123...");
  Serial.print("count=");
  Serial.println(count);
}

void loop() {
  count = count + 1;
  Serial.print("c : ");
  Serial.println(count);
  delay(1000);
}

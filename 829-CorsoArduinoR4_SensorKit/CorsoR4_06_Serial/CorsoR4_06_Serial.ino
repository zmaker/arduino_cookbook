//variabile globale
int count = 0;

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Hello Arduino!");
}

void loop() {
  Serial.print("count: ");
  Serial.print(count);
  Serial.print("\n");
  delay(1000);
  count = count + 1;
}

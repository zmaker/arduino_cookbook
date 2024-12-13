void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(1);
  }

  int n = 123;
  int &pr = n;

  Serial.print("valore riferito da r: ");Serial.println(pr);
  pr = 99;
  Serial.print("valore riferito da r: ");Serial.println(pr);
  Serial.print("valore n: ");Serial.println(n);

  
}

void loop() {
  // put your main code here, to run repeatedly:

}

void setup() {
  Serial.begin(115200);

  int x = 36;
  float y = 1.2;

  Serial.printf("x vale: %d \n", x);
  Serial.printf("y: %f oppure y: %.2f \n", y, y);

  char str[] = "Hello World!";
  Serial.printf("La stringa: %s \n", str);

  x = 0x1A;
  Serial.printf("numero esadecimale : %02x \n", x);

  int h = 12;
  int m = 2;
  int s = 3;
  Serial.printf("orario : %02i:%02i:%02i \n", h,m,s);

}

void loop() {}

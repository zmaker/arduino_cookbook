void setup() {
  Serial.begin(9600);
}

void loop() {
  int id = 123;
  int temp = 34;
  char stato[] = "ok";

  char buf[30];
  sprintf(buf, "[%d] t:%d  - %s", id, temp, stato);
  Serial.println(buf);

  float hum = 12.3;
  char tmp[10];
  dtostrf(hum, 6, 2, tmp);

  snprintf(buf, sizeof(buf), "[%d] t:%d h:%s - %s", id, temp, tmp, stato);
  //snprintf(buf, sizeof(buf), "[%d] t:%d h:%f - %s", id, temp, hum, stato);
  Serial.println(buf);

  delay(1000);
}

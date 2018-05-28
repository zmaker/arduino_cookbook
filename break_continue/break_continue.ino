void setup() {
  Serial.begin(9600);
  
  int i = 0;
  while (i < 10) {
    if (i == 3) continue;
    Serial.println(i);
    i++;
  }
  
}

void loop(){
}

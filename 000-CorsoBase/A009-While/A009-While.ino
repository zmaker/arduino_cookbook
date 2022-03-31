void setup() {
  Serial.begin(9600);

  int c = 0;
  while (c < 10) {
    //corpo del ciclo while  
    delay(200);
    c++;
    if (c == 5) continue; 
    //if (c == 5) break; 
    Serial.print("c: ");
    Serial.println(c);
  }
  Serial.println("end");

  Serial.println("do-while");
  c = 0;
  do {
    c++;
    Serial.print("dw: ");
    Serial.println(c);
  } while (c < 4);
  
}

void loop() {
  
}

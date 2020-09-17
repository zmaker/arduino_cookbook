void setup() {
  Serial.begin(115200);
}

int buff[128];

void loop() {

  float n = (float)analogRead(A0);
  
  for (int i = 0; i < 128; i++){
    //buff[i] = analogRead(A0);  
    
    float ang = ((float)(i) * PI) / (n + 1);
    
    buff[i] = 512 + (200.0 * sin(ang)) + random(1, 10);
  }

  for (int x = 0; x < 128; x++){
    Serial.print(buff[x]);
    if (x < 128) Serial.print(";");  
  }
  Serial.print("\n");
  
  delay(100);  
}

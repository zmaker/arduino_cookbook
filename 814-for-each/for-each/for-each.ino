
void setup() {
  Serial.begin(9600);

  int n[5] = {1, 2, 3, 4, 5};
  for (int e : n) {
    Serial.print("> ");Serial.println(e);    
  }
  
}

void loop() {}

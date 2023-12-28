
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));

  int n[5] = {1, 2, 3, 4, 5};
  int * ptr = n;

  Serial.println("print array");
  for (int i = 0; i < 5; i++) {
    Serial.print(i);Serial.print(" - ");Serial.println(n[i]);
  }

  Serial.println("print array con ptr");
  for (int i = 0; i < 5; i++) {
    Serial.print(i);Serial.print(" - ");Serial.println(*ptr);
    ptr++;
  }
 
  Serial.println("print array con ref");
  int(&ref_to_n)[5] = n;
  for (int i = 0; i < 5; i++) {
    Serial.print(i);Serial.print(" - ");Serial.println(ref_to_n[i]);
  }
  
  /*for (int e : ref_to_n) {
    Serial.print("> ");Serial.println(e);    
  }
  */
  
}

void loop() {}

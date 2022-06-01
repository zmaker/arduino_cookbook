
void setup () {
  pinMode(10, OUTPUT);
}

void loop () {
  for (int i = 0; i <=255; i++){
    analogWrite(10, i);
    delay(10);  
  }
  for (int i = 255; i >= 0; i--){
    analogWrite(10, i);
    delay(10);  
  }
}

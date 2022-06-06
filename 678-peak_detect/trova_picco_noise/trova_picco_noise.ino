int picco = 0;
int soglia = 0;
int rumore = 5;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  determina_soglia();
  Serial.print("soglia: ");Serial.println(soglia);
}

void loop() {
  int v = analogRead(A1);
  if (v > picco) {
    picco = v;  
  }
  if (v <= (soglia - rumore)) {
    if (picco > (soglia + rumore)) {
      Serial.print(picco);Serial.println("\t PICCO!");
      picco = 0;
      digitalWrite(13, HIGH);
      delay(200);  
      digitalWrite(13, LOW);
    }  
  }
  //Serial.println(v);
  //delay(200);
}

void determina_soglia(){
  int v = analogRead(A1);
  int vmax = 1023;

  soglia = v + (vmax - v)/2;
}

int soglia = 0;
bool stato = LOW;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);

  digitalWrite(13, HIGH);
  calibra();
  digitalWrite(13, LOW);
  String str = "soglia: " + String(soglia);
  Serial.println(str);
}

void loop() {
  int n = analogRead(A0);
  //Serial.println(n);
  if (n > soglia) {
    stato = !stato;
    delay(100);
  } 
  digitalWrite(13, stato);   
}

void calibra() {
  for (int i = 0; i < 100; i++) {
    soglia += analogRead(A0);  
    delay(50);
  }  
  soglia = soglia/100;
  soglia = (int)((float)soglia * 1.2f);
}

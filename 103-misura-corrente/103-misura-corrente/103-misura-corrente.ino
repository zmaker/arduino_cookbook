void setup() {
  Serial.begin(9600);
}

void loop() {
  //campiono 10 valori e calcolo la media
  int val = 0;
  for (int i = 0; i < 10; i++) {
    val += analogRead(A0);
    delay(10);
  }
  val = val / 10;

  //ricavo la tensione sul pin A0. 4.88 = 5000 mV / 1024 campioni
  float tensione = 4.88 * val;

  float corrente = (tensione - 2500);

  Serial.print("I = ");
  Serial.println(corrente);
  
  delay(1000);  
}


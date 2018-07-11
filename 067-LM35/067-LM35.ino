/*
10mV per ogni grado Celsius

*/

void setup() {
  Serial.begin(9600);
}

void loop() {
  int v = analogRead(A0);
  Serial.println(v);  

  double vt = (float)(5000.0d/1024.0d)*(float)v;
  Serial.print("tensione: ");
  Serial.print(vt);
  Serial.println(" mV");

  double temp = vt/10.0d;
  Serial.print("temp: ");
  Serial.print(temp);
  Serial.println("°C");

  delay(1000);
}

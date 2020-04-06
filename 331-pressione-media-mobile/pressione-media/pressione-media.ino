void setup() {
  Serial.begin(9600);
}

int const fsize = 50;
int fil[fsize];
int i = 0;
float avg = 0.0;

void loop() {
  int s = analogRead(A0);

  fil[i] = s;
  if (i < (fsize-1)) i++;
  else i = 0;

  for (int j = 0; j < fsize; j++) {
    avg += (float)fil[j];  
  }
  avg = avg / (float)(fsize+1);
  
  Serial.print(s);Serial.print(",");Serial.println(avg);
  delay(10);
}

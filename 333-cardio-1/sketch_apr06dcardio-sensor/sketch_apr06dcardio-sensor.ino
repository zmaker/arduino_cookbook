void setup() {
  Serial.begin(9600);
}

unsigned long dt, t1;
int t_sample = 20;

long sum;
float avg = 0;
int campioni = 0;

void loop() {
  dt = millis() - t1;
  if (dt < t_sample) {
    sum += analogRead(A0);
    campioni++;
  } else {
    avg = sum / (float)campioni;
    campioni = 0;
    sum = 0;
    t1 = millis();
    Serial.println(avg);
  } 

}


void storeValues(float * t, float * v);
void storeValuesR(float & t, float & v);

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));

  float temp, vel;
  storeValues(&temp, &vel);
  Serial.print("1. t: ");Serial.print(temp);
  Serial.print("\tv: ");Serial.println(vel);

  temp = 0;
  vel = 0;
  storeValuesR(temp, vel);
  Serial.print("2. t: ");Serial.print(temp);
  Serial.print("\tv: ");Serial.println(vel);

}

void loop() {}

void storeValues(float *t, float *v) {
  //fun che restituisce 2 valori
  *t = random(50);
  *v = random(100);
}

void storeValuesR(float &t, float &v) {
  //fun che restituisce 2 valori
  t = random(50);
  v = random(100);
}

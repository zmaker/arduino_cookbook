const int SENSOR_PIN = A0;
const int NUM_SAMPLES = 100;      // quanti campioni (cicli di rete) per "treno"

int buff[NUM_SAMPLES];

void setup() {
  Serial.begin(115200);
}

void loop() {
  for (int i = 0; i < NUM_SAMPLES; i++) {
    buff[i] = analogRead(SENSOR_PIN);
    delayMicroseconds(1000);
  }

  int minVal = buff[0];
  int maxVal = buff[0];
  for (int i = 0; i < NUM_SAMPLES; i++) {
    if (buff[i] < minVal) minVal = buff[i];
    if (buff[i] > maxVal) maxVal = buff[i];
  }

  int midpoint = ((maxVal - minVal) / 2) + minVal;
  float sumSq = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    float centered = buff[i] - midpoint;
    sumSq += (float)centered * centered;
  }

  float rmsVal = sqrt( sumSq / NUM_SAMPLES) * 8.42;

  Serial.print(F("Vrms: "));
  Serial.print(rmsVal, 1);
  Serial.println(F(" V"));
  delay(500);
}

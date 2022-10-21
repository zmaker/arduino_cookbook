int sinusoide[256];

void setup() {
  Serial.begin(115200);

  float passo = (2.0 * PI) / 256.0;
  for (int i = 0; i < 256; i++) {
    float angolo = passo * (float)i;
    sinusoide[i] = 128 + (int)(sin(angolo) * 127.0);
    Serial.print(angolo);
    Serial.print("\t sin=");
    Serial.println(sinusoide[i]);    
  }

}

void loop() {
  for (int i = 0; i < 256; i++) {
    dacWrite(25, sinusoide[i]);
    delay(1);
  }

}

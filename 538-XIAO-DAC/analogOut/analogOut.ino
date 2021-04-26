/**
 * Seeeduino XIAO
 * Link per installare la scheda
 * https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
 */

void setup() {
  Serial.begin(9600);
  analogWriteResolution(10);
}

int a = 0;
float r = 0.0;

void loop() {
  a++;
  if (a >= 360) a = 0;
  r = (PI * (float)a) / 180.0f;
  float n = sin(r);  
  Serial.println(n);
  
  int val = (int)(511.5 + 511.5 * n);
   
  analogWrite(0, val); 
  delay(1);
}

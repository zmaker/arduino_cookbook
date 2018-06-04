/*
 * https://www.arduino.cc/en/Tutorial/ColorCrossfader
 */

void setup() {  
  randomSeed(analogRead(A0));
  Serial.begin(9600);
}

void loop() { 
  int r = random(0, 256);
  int g = random(0, 256);
  int b = random(0, 256);

  Serial.print("r=");
  Serial.print(r);
  Serial.print(" g=");
  Serial.print(g);
  Serial.print(" b=");
  Serial.println(b);
  
  analogWrite(9, r);
  analogWrite(10, g);
  analogWrite(11, b);
  delay(500);
}

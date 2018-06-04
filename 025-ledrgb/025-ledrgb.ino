/*
 * vedi anche 
 * colorcrossfader
 * 
 * https://www.arduino.cc/en/Tutorial/ColorCrossfader
 */

void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {  
  int r = random(0,256);
  int g = random(0,256);
  int b = random(0,256);

  analogWrite(9, r);
  analogWrite(10, g);
  analogWrite(11, b);

  delay(500);
}

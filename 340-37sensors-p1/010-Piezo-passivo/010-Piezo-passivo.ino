/**
 * 010 - Piezo passivo 
 * basato sullo sketch 021
 * https://github.com/zmaker/arduino_cookbook/blob/master/021-tone/021-tone/021-tone.ino
 * 
 */

const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;

int pin = 6;

void setup() {
  pinMode(pin, OUTPUT);  

  tone(pin, a, 500);
  delay(500);
  tone(pin, b, 500);
  delay(500);
  tone(pin, c, 500);
  delay(500);
  tone(pin, d, 500);
  delay(500);
}

void loop() {
}

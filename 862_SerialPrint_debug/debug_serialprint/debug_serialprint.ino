/*
Sketch uses 1920 bytes (5%) of program storage space. Maximum is 32256 bytes.
Global variables use 202 bytes (9%) of dynamic memory, leaving 1846 bytes for local variables. Maximum is 2048 bytes.
*/

#define DEBUG 0

#if DEBUG
  #define prt(x) Serial.print(x);
  #define prtn(x) Serial.println(x);
#else 
  #define prt(x) 
  #define prtn(x)
#endif

int v = 0;

void setup() {
  Serial.begin(9600);
  prtn("My Sketch");
}

void loop() {
  prt("v:");prtn(v);
  v++;
  delay(1000);
}

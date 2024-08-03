#include "Modulino.h"
ModulinoMovement movement;

float x;
float y;
float z;

#include "Arduino_LED_Matrix.h"
ArduinoLEDMatrix matrix;

byte frame[8][12] = {
{0,0,0,0, 0,0,0,0, 0,0,0,0},
{0,0,0,0, 0,0,0,0, 0,0,0,0},
{0,0,0,0, 0,0,0,0, 0,0,0,0},
{0,0,0,0, 0,0,0,0, 0,0,0,0},
{0,0,0,0, 0,0,0,0, 0,0,0,0},
{0,0,0,0, 0,0,0,0, 0,0,0,0},
{0,0,0,0, 0,0,0,0, 0,0,0,0},
{0,0,0,0, 0,0,0,0, 0,0,0,0}
};

const int display_width = 12;
const int display_height = 8;
unsigned long t1;

void setup() {
  Serial.begin(115200);
  Modulino.begin();
  movement.begin();
  matrix.begin();
}

void loop() {
  movement.update();

  x = movement.getX();
  y = movement.getY();
  z = movement.getZ();

  float pitch = accToAngle(y, x, z);
  float roll = accToAngle(x, y, z);

  /*Serial.print("r: ");
  Serial.print(roll);
  Serial.print("\tp: ");
  Serial.println(pitch);
*/
  if ((millis() - t1) > 100) {
    clearDisplay();

    int xp = display_height / 2 + 10.0 * sin(toRad(pitch));
    int yp = display_width / 2 + 10.0 * sin(toRad(roll));
    
    Serial.print("x: ");
  Serial.print(xp);
  Serial.print("\ty: ");
  Serial.println(yp);
    setPix(xp,yp,1);
  matrix.renderBitmap(frame, 8, 12);
    t1 = millis();
  }
}

float toRad(float ang) {
  return (ang * PI) / 180.0;
}

float accToAngle(float a, float b, float c) {
  float d = sqrt(a * a + c * c);
  float ang = atan2(b, d);
  ang = (ang * 180.0) / PI;
  return ang;
}

void clearDisplay(){
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 12; j++) {
      frame[i][j] = 0;
    }
  }
}

void setPix(int x, int y, byte val){
  x = constrain(x, 0, 11);
  y = constrain(y, 0, 7);
  frame[7-y][x] = val;
}
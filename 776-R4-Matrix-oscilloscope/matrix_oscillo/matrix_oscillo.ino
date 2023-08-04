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

int x = 0;
int y = 0;

void setup() {
  Serial.begin(115200);
  matrix.begin();

}

void loop() {
  //clearDisplay();

  int v = analogRead(A0);
  y = map(v, 0, 1024, 0, 12);
  setPix(x,y, 1);

  x++;
  if (x >= 12) {
    x = 0;
    clearDisplay();
  }

  matrix.renderBitmap(frame, 8, 12);
  delay(50);
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




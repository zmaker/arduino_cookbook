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

int c = 0;

void setup() {
  matrix.begin();
  Serial.begin(115200);
}

void loop() {
  clearDisplay();
  
  int u = c % 10;
  int d = (c/10) % 10;
  int cc = (c/100) % 10;
  int m = (c/1000) % 10;

  digit(u, 9,0);
  digit(d, 6,0);
  digit(cc, 3,0);
  digit(m, 0,0);

  matrix.renderBitmap(frame, 8, 12);
  delay(100);
  c++;
  if (c > 9999) c = 0;
  Serial.println(c);
}

void clearDisplay(){
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 12; j++) {
      frame[i][j] = 0;
    }  
  }
}

void digit(int n, int offx, int offy){
  switch(n) {
    case 0:
      frame[offy][offx+0] = 1;
      frame[offy][offx+1] = 1;
      frame[offy][offx+2] = 1;

      frame[offy+1][offx+0] = 1;
      frame[offy+1][offx+1] = 0;
      frame[offy+1][offx+2] = 1;

      frame[offy+2][offx+0] = 1;
      frame[offy+2][offx+1] = 0;
      frame[offy+2][offx+2] = 1;

      frame[offy+3][offx+0] = 1;
      frame[offy+3][offx+1] = 0;
      frame[offy+3][offx+2] = 1;

      frame[offy+4][offx+0] = 1;
      frame[offy+4][offx+1] = 1;
      frame[offy+4][offx+2] = 1;
      break;
    case 1:
      frame[offy][offx+0] = 0;
      frame[offy][offx+1] = 1;
      frame[offy][offx+2] = 1;

      frame[offy+1][offx+0] = 0;
      frame[offy+1][offx+1] = 0;
      frame[offy+1][offx+2] = 1;

      frame[offy+2][offx+0] = 0;
      frame[offy+2][offx+1] = 0;
      frame[offy+2][offx+2] = 1;

      frame[offy+3][offx+0] = 0;
      frame[offy+3][offx+1] = 0;
      frame[offy+3][offx+2] = 1;

      frame[offy+4][offx+0] = 0;
      frame[offy+4][offx+1] = 0;
      frame[offy+4][offx+2] = 1;
      break;
    case 2:
    frame[offy][offx+0] = 1;
    frame[offy][offx+1] = 1;
    frame[offy][offx+2] = 1;

    frame[offy+1][offx+0] = 0;
    frame[offy+1][offx+1] = 0;
    frame[offy+1][offx+2] = 1;

    frame[offy+2][offx+0] = 1;
    frame[offy+2][offx+1] = 1;
    frame[offy+2][offx+2] = 1;

    frame[offy+3][offx+0] = 1;
    frame[offy+3][offx+1] = 0;
    frame[offy+3][offx+2] = 0;

    frame[offy+4][offx+0] = 1;
    frame[offy+4][offx+1] = 1;
    frame[offy+4][offx+2] = 1;
    break;
    case 3:
    frame[offy][offx+0] = 1;
    frame[offy][offx+1] = 1;
    frame[offy][offx+2] = 1;

    frame[offy+1][offx+0] = 0;
    frame[offy+1][offx+1] = 0;
    frame[offy+1][offx+2] = 1;

    frame[offy+2][offx+0] = 1;
    frame[offy+2][offx+1] = 1;
    frame[offy+2][offx+2] = 1;

    frame[offy+3][offx+0] = 0;
    frame[offy+3][offx+1] = 0;
    frame[offy+3][offx+2] = 1;

    frame[offy+4][offx+0] = 1;
    frame[offy+4][offx+1] = 1;
    frame[offy+4][offx+2] = 1;
    break;
    case 4:
    frame[offy][offx+0] = 1;
    frame[offy][offx+1] = 0;
    frame[offy][offx+2] = 1;

    frame[offy+1][offx+0] = 1;
    frame[offy+1][offx+1] = 0;
    frame[offy+1][offx+2] = 1;

    frame[offy+2][offx+0] = 1;
    frame[offy+2][offx+1] = 1;
    frame[offy+2][offx+2] = 1;

    frame[offy+3][offx+0] = 0;
    frame[offy+3][offx+1] = 0;
    frame[offy+3][offx+2] = 1;

    frame[offy+4][offx+0] = 0;
    frame[offy+4][offx+1] = 0;
    frame[offy+4][offx+2] = 1;
    break;
    case 5:
    frame[offy][offx+0] = 1;
    frame[offy][offx+1] = 1;
    frame[offy][offx+2] = 1;

    frame[offy+1][offx+0] = 1;
    frame[offy+1][offx+1] = 0;
    frame[offy+1][offx+2] = 0;

    frame[offy+2][offx+0] = 1;
    frame[offy+2][offx+1] = 1;
    frame[offy+2][offx+2] = 1;

    frame[offy+3][offx+0] = 0;
    frame[offy+3][offx+1] = 0;
    frame[offy+3][offx+2] = 1;

    frame[offy+4][offx+0] = 1;
    frame[offy+4][offx+1] = 1;
    frame[offy+4][offx+2] = 1;
    break;
    case 6:
    frame[offy][offx+0] = 1;
    frame[offy][offx+1] = 0;
    frame[offy][offx+2] = 0;

    frame[offy+1][offx+0] = 1;
    frame[offy+1][offx+1] = 0;
    frame[offy+1][offx+2] = 0;

    frame[offy+2][offx+0] = 1;
    frame[offy+2][offx+1] = 1;
    frame[offy+2][offx+2] = 1;

    frame[offy+3][offx+0] = 1;
    frame[offy+3][offx+1] = 0;
    frame[offy+3][offx+2] = 1;

    frame[offy+4][offx+0] = 1;
    frame[offy+4][offx+1] = 1;
    frame[offy+4][offx+2] = 1;
    break;
    case 7:
    frame[offy][offx+0] = 1;
    frame[offy][offx+1] = 1;
    frame[offy][offx+2] = 1;

    frame[offy+1][offx+0] = 0;
    frame[offy+1][offx+1] = 0;
    frame[offy+1][offx+2] = 1;

    frame[offy+2][offx+0] = 0;
    frame[offy+2][offx+1] = 0;
    frame[offy+2][offx+2] = 1;

    frame[offy+3][offx+0] = 0;
    frame[offy+3][offx+1] = 0;
    frame[offy+3][offx+2] = 1;

    frame[offy+4][offx+0] = 0;
    frame[offy+4][offx+1] = 0;
    frame[offy+4][offx+2] = 1;
    break;
    case 8:
    frame[offy][offx+0] = 1;
    frame[offy][offx+1] = 1;
    frame[offy][offx+2] = 1;

    frame[offy+1][offx+0] = 1;
    frame[offy+1][offx+1] = 0;
    frame[offy+1][offx+2] = 1;

    frame[offy+2][offx+0] = 1;
    frame[offy+2][offx+1] = 1;
    frame[offy+2][offx+2] = 1;

    frame[offy+3][offx+0] = 1;
    frame[offy+3][offx+1] = 0;
    frame[offy+3][offx+2] = 1;

    frame[offy+4][offx+0] = 1;
    frame[offy+4][offx+1] = 1;
    frame[offy+4][offx+2] = 1;
    break;
    case 9:
    frame[offy][offx+0] = 1;
    frame[offy][offx+1] = 1;
    frame[offy][offx+2] = 1;

    frame[offy+1][offx+0] = 1;
    frame[offy+1][offx+1] = 0;
    frame[offy+1][offx+2] = 1;

    frame[offy+2][offx+0] = 1;
    frame[offy+2][offx+1] = 1;
    frame[offy+2][offx+2] = 1;

    frame[offy+3][offx+0] = 0;
    frame[offy+3][offx+1] = 0;
    frame[offy+3][offx+2] = 1;

    frame[offy+4][offx+0] = 1;
    frame[offy+4][offx+1] = 1;
    frame[offy+4][offx+2] = 1;
    break;
  }
}




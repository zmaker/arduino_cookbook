#include <Arduino.h>
#include <Wire.h>
#include <BMx280I2C.h>

#define I2C_ADDRESS 0x76

BMx280I2C bmx280(I2C_ADDRESS);

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

void setup() {
  Serial.begin(115200);
  matrix.begin();
  Wire.begin();

	if (!bmx280.begin()) {
		Serial.println("begin() failed. check your BMx280 Interface and I2C Address.");
		while (1);
	}
	bmx280.resetToDefaults();
  bmx280.writeOversamplingPressure(BMx280MI::OSRS_P_x16);
	bmx280.writeOversamplingTemperature(BMx280MI::OSRS_T_x16);

}

void loop() {
  clearDisplay();

  bmx280.measure();
  do {
    delay(100);
  } while (!bmx280.hasValue());

  int temp = (int)bmx280.getTemperature();

  int u = temp % 10;
  int d = (temp/10) % 10;
  int c = (temp/100) % 10;

  digit(u, 9, 1);
  if (temp >= 10) digit(d, 5, 1);
  if (temp >= 100) digit(c, 1, 1);

  matrix.renderBitmap(frame, 8, 12);
  delay(500);
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

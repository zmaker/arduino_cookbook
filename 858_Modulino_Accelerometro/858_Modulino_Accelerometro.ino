#include "Modulino.h"

ModulinoMovement movement;

float x;
float y;
float z;

void setup() {
  Serial.begin(115200);
  Modulino.begin();
  movement.begin();
}

void loop() {
  movement.update();

  x = movement.getX();
  y = movement.getY();
  z = movement.getZ();

  Serial.print("Movement data: ");
  Serial.print("x ");
  Serial.print(x, 3);
  Serial.print("	y ");
  Serial.print(y, 3);
  Serial.print("	z ");
  Serial.println(z, 3);
}
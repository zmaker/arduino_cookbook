#include "Arduino_LED_Matrix.h"
//https://ledmatrix-editor.arduino.cc/
#include "animation.h"

ArduinoLEDMatrix matrix;

void setup() {
  matrix.begin();

  // turn on autoscroll to avoid calling next() to show the next frame; the paramenter is in milliseconds
  //matrix.autoscroll(500);
  //play the animation on the matrix
  //matrix.play(true);

}

void loop() {
  matrix.loadFrame(animation[0]);
  delay(500);
  matrix.loadFrame(animation[1]);
  delay(500);
}

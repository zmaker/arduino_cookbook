#include <ArduinoGraphics.h> 
#include <Arduino_LED_Matrix.h>

ArduinoLEDMatrix matrix;

void setup() {
  matrix.begin();

  matrix.beginDraw();
  const char text[] = "ABC";
  matrix.textFont(Font_4x6);
  matrix.beginText(0,0, 0xFFFFFF); //x,y,colore
  matrix.println(text);
  matrix.endText();
  matrix.endDraw();

  matrix.clear();
}

void loop() {
  matrix.beginDraw();
  matrix.textScrollSpeed(30);
  const char text[] = "    Hello World!    ";
  matrix.textFont(Font_5x7);
  matrix.beginText(0,1, 0xFFFFFF); //x,y,colore
  matrix.println(text);
  matrix.endText(SCROLL_LEFT);
  matrix.endDraw();
}

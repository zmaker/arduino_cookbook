#include <Modulino.h>
#include <ArduinoGraphics.h> 
#include <Arduino_LED_Matrix.h>

ModulinoThermo sens;
float temp, hum;

ArduinoLEDMatrix matrix;

char msg[30];

void setup() {
  Serial.begin(115200);
  Modulino.begin();
  sens.begin();
  matrix.begin();
}

void loop() {
  temp = sens.getTemperature();
  hum = sens.getHumidity();
  
  sprintf(msg, " %d.%dC %d.%d%% ", (int)temp, (int)(temp*10)%10, (int)hum, (int)(hum*10)%10);     

  matrix.beginDraw();
  matrix.textScrollSpeed(70);
  matrix.textFont(Font_5x7);
  matrix.beginText(0,1,0xFFFFFF);
  matrix.println(msg);
  matrix.endText(SCROLL_LEFT);
  matrix.endDraw();
}

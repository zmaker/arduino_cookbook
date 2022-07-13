#include "Gauge.h"

Gauge::Gauge(int x, int y, int r){
  this->xc = x;
  this->yc = y;
  this->raggio = (float)r;
}

void Gauge::setValue(int p){
  float a = (2.0 * PI * (float)p) / 100.0;
  a = a - (PI/2.0);  
  int xp = this->xc + (int)(cos(a) * this->raggio);
  int yp = this->yc + (int)(sin(a) * this->raggio);

  this->display->clearDisplay();    
  this->display->drawCircle(this->xc,this->yc, this->raggio, SSD1306_WHITE);
  this->display->drawLine(this->xc,this->yc, xp,yp, SSD1306_WHITE); //lancetta
  this->display->drawLine(this->xc,this->yc - this->raggio, 
    this->xc,this->yc - (this->raggio - this->raggio/5), SSD1306_WHITE); //tacca
  this->display->display();    
}

void Gauge::setDisplay(Adafruit_SSD1306 *display){
  this->display = display;
}

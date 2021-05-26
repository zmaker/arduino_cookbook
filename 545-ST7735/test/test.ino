// https://github.com/olikraus/ucglib/wiki

#include <SPI.h>
#include "Ucglib.h"
Ucglib_ST7735_18x128x160_HWSPI ucg(/*cd=*/ 3, /*cs=*/ 10, /*reset=*/ 8);

void setup() {  
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.setFont(ucg_font_helvB08_hr);
  ucg.clearScreen();
}

int y = 0;
unsigned long t1, dt;

void loop(void){
  dt = millis() - t1;
  if (dt > 500) {
    ucg.setColor(0,0,0);
    ucg.drawBox(0, y, 50, 30);
    
    ucg.setColor(255, 255, 255);
    ucg.setPrintPos(2,y+10);  
    ucg.print("Hello");
      
    y++;
    if (y >= 100) y = 0;
    
    t1 = millis();
  }
}

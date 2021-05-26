#include <SPI.h>
#include "Ucglib.h"
Ucglib_ST7735_18x128x160_HWSPI ucg(/*cd=*/ 3, /*cs=*/ 10, /*reset=*/ 8);

void setup(void) {
  delay(1000);
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  //ucg.begin(UCG_FONT_MODE_SOLID);
  ucg.clearScreen();
}

int count = 0;

void loop(void) {
  //ucg.setRotate90();
  ucg.setFont(ucg_font_ncenR12_tr);
  ucg.setColor(255, 255, 255);
  //ucg.setColor(0, 255, 0);
  ucg.setColor(1, 255, 0,0);
  
  ucg.setPrintPos(0,25);
  ucg.print("Hello World!");

  ucg.setColor(255, 0, 0);
  ucg.setPrintPos(0,50);
  ucg.print(count);
  count++;
  delay(1000); 
  ucg.clearScreen(); 
}

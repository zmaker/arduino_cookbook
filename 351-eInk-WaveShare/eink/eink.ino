//https://www.waveshare.com/product/1.54inch-e-Paper-Module.htm

#include <GxEPD.h>
#include <GxGDEH0154D67/GxGDEH0154D67.h>  // 1.54" b/w
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#include <Fonts/FreeMonoBold9pt7b.h>
//#include <Fonts/FreeMonoBold12pt7b.h>
//#include <Fonts/FreeMonoBold18pt7b.h>
//#include <Fonts/FreeMonoBold24pt7b.h>

GxIO_Class io(SPI, /*CS=*/ 10, /*DC=*/ 9, /*RST=*/ 8 );
GxEPD_Class display(io, /*RST=*/ 8, /*BUSY=*/ 7); 

void setup() {
  display.init();
  display.eraseDisplay();
  display.drawPaged(drawHelloWorld);
}

void loop() {  
}

void drawHelloWorld() {
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeMonoBold9pt7b);  
  
  display.setCursor(0, 15);
  display.print(F("zeppelinmaker.it"));
  display.setCursor(0, 40);
  display.print(F("Hello World!"));
}

#include "config.h"
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

void setupDisplay() {
  // Module configuration
  HUB75_I2S_CFG mxconfig(
    PANEL_RES_X, // Module width
    PANEL_RES_Y, // Module height
    PANEL_CHAIN, // chain length
    _pins // pin mapping
  );

  //mxconfig.gpio.e = 18;
  //mxconfig.clkphase = true;
  //mxconfig.driver = HUB75_I2S_CFG::FM6126A;

  // Display Setup
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);
  dma_display->begin();
  dma_display->setBrightness8(90); //0-255
  dma_display->clearScreen();
}

void showMessage(String msg){
  dma_display->clearScreen();
  dma_display->setTextSize(1);
  dma_display->setTextWrap(false); 
  dma_display->setTextColor(myWHITE);
  dma_display->setCursor(2, 2);  
  dma_display->println(msg);
}

void clock(int hh, int mm, int ss) {
  int SCREEN_WIDTH = PANEL_RES_X;
  int SCREEN_HEIGHT = PANEL_RES_Y;

  const float r = (SCREEN_HEIGHT/2) - 5;
  const float rh = (SCREEN_HEIGHT/2) * 0.5;
  const float rm = (SCREEN_HEIGHT/2) * 0.8;
  const float rse = 14;
  const float rsi = 12;

  float a = 0;
  //ore
  a = (6.28/12.0) * (float)hh;
  int xh = SCREEN_WIDTH/2 + rh*sin(a);
  int yh = SCREEN_HEIGHT/2 - rh*cos(a);
  dma_display->drawLine(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, xh, yh, myWHITE);
  //min
  a = (6.28/60.0) * (float)mm;
  int xm = SCREEN_WIDTH/2 + rm*sin(a);
  int ym = SCREEN_HEIGHT/2 - rm*cos(a);
  dma_display->drawLine(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, xm, ym, myWHITE);
  //secondi
  a = (6.28/60.0) * (float)ss;
  int xe = SCREEN_WIDTH/2 + rse*sin(a);
  int ye = SCREEN_HEIGHT/2 - rse*cos(a);
  int xi = SCREEN_WIDTH/2 + rsi*sin(a);
  int yi = SCREEN_HEIGHT/2 - rsi*cos(a);
  dma_display->drawLine(xi,yi, xe,ye, myRED);

  //corona  
  dma_display->drawCircle(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 15, myWHITE);
} 

  
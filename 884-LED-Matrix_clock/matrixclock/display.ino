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


  
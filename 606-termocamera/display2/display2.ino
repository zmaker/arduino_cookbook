#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
MCUFRIEND_kbv tft;

#include <Melopero_AMG8833.h>
Melopero_AMG8833 sensor;

void setup() {
  Serial.begin(9600);

  Wire.begin();
  sensor.initI2C();
  Serial.print("Resetting sensor ... ");  
  int statusCode = sensor.resetFlagsAndSettings();
  Serial.println(sensor.getErrorDescription(statusCode));

  Serial.print("Setting FPS ... ");
  statusCode = sensor.setFPSMode(FPS_MODE::FPS_10);
  Serial.println(sensor.getErrorDescription(statusCode));
  
  
  delay(100);
  
  int id = tft.readID();
  tft.begin(id);

  //tft.setRotation(1); 
  //tft.setTextSize(2);
  //tft.setTextColor(0xFFFF, 0x0000);
  tft.fillScreen(BLACK);
}

void loop() {
  int n = sensor.updatePixelMatrix();

  for (int x = 0; x < 8; x++){
    for (int y = 0; y < 8; y++){
      Serial.print(sensor.pixelMatrix[y][x]);
      Serial.print(" ");
      tft.fillRect(y*8, x*8, 8, 8, (int)map(sensor.pixelMatrix[y][x], 14, 25, 0, 32));
    }
  }
  Serial.println(" "); 
  delay(200);
}

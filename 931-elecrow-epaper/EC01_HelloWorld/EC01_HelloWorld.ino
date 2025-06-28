#include "EPD.h"
#include "icone.h"

// ESP32S3 Dev Module
// https://javl.github.io/image2cpp/


uint8_t img[27200];

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("epaper");

  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);

  EPD_GPIOInit();
  Paint_NewImage(img, EPD_W, EPD_H, Rotation, WHITE);
  Paint_Clear(WHITE);

  EPD_FastMode1Init();
  EPD_Display_Clear();
  EPD_Update();
  EPD_Clear_R26A6H();

  EPD_ShowString(1,1, "Hello ePaper!", 24, BLACK);
  EPD_ShowString(1,26, "www.zeppelinmaker.it - Font 16", 16, BLACK);
  EPD_DrawLine(0, 200, 792, 200, BLACK);

  EPD_ShowPicture(300, 0, 128, 128, bmp1, BLACK);

  EPD_Display(img);
  EPD_PartUpdate();
  EPD_DeepSleep();
}

void loop() {
  delay(100);
}

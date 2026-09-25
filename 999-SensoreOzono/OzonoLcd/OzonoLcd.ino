// https://github.com/DFRobot/DFRobot_OzoneSensor
#include "DFRobot_OzoneSensor.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define COLLECT_NUMBER   20              // campioni per la media (1-100)
#define Ozone_IICAddress OZONE_ADDRESS_3 // 0x73
#define LCD_ADDRESS      0x27            // prova 0x3F se non vedi nulla
#define WARMUP_SEC       180

LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);
DFRobot_OzoneSensor Ozone;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.print("Sensore Ozono");

  while (!Ozone.begin(OZONE_ADDRESS_3)){
    Serial.println("Sensore non trovato su I2C!");
    lcd.setCursor(0,1);
    lcd.print("Sensore assente!");
    delay(1000);
  } 
  Serial.println("Sensore OK");
  Ozone.setModes(MEASURE_MODE_PASSIVE);

  for (int s = WARMUP_SEC; s > 0; s--){
    lcd.setCursor(0,1);
    lcd.print("Warm-up: ");
    lcd.print(s);
    lcd.print("s        ");
    delay(1000);
  }
  lcd.clear();
}

void loop() {
  int16_t ppb = Ozone.readOzoneData(COLLECT_NUMBER);
  float ppm = ppb / 1000.0;

  lcd.setCursor(0,0);
  lcd.print("O3: ");
  lcd.print(ppb);
  lcd.print(" ppb      ");

  lcd.setCursor(0,1);
  lcd.print("    ");
  lcd.print(ppm, 3);
  lcd.print(" ppm      ");

  Serial.print("Ozono: ");
  Serial.print(ppb);
  Serial.println(" ppb");
  delay(1000);
}

/******************************************************************************
  Read basic CO2 and TVOCs

  https://github.com/sparkfun/CCS811_Air_Quality_Breakout
  https://github.com/sparkfun/SparkFun_CCS811_Arduino_Library

  Read the TVOC and CO2 values from the SparkFun CSS811 breakout board

  A new sensor requires at 48-burn in. Once burned in a sensor requires
  20 minutes of run in before readings are considered good.

  Hardware Connections (Breakoutboard to Arduino):
  3.3V to 3.3V pin
  GND to GND pin
  SDA to A4
  SCL to A5

******************************************************************************/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "SparkFunCCS811.h" //Click here to get the library: http://librarymanager/All#SparkFun_CCS811

//#define CCS811_ADDR 0x5B //Default I2C Address
#define CCS811_ADDR 0x5A //Alternate I2C Address

CCS811 mySensor(CCS811_ADDR);

Adafruit_SSD1306 display(128, 32, &Wire, -1);

void setup() {
  Serial.begin(9600);
  Serial.println("CCS811 Basic Example");

  Wire.begin(); //Inialize I2C Hardware

  if (mySensor.begin() == false) {
    Serial.print("CCS811 error. Please check wiring. Freezing...");
    while (1);
  }

  //display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  display.clearDisplay();
}
char str[10];

void loop() {
  if (mySensor.dataAvailable()) {
    mySensor.readAlgorithmResults();
    int co2 = mySensor.getCO2();
    int tvoc = mySensor.getTVOC();
    Serial.print("CO2[");
    Serial.print(co2);
    Serial.print("] tVOC[");
    Serial.print(tvoc);
    Serial.println("]");

    display.clearDisplay();
    display.setCursor(0,0);
    sprintf(str, "%d", co2);
    display.write("CO2: ");
    display.write(str);
    display.setCursor(0,16);
    display.write("TVOC: ");
    sprintf(str, "%d", tvoc);
    display.write(str);
    display.display();
  }

  delay(100); //Don't spam the I2C bus
}

/* Get tilt angles on X and Y, and rotation angle on Z
 * Angles are given in degrees
 * 
 * License: MIT
 */

#include "Wire.h"
#include <MPU6050_light.h>
MPU6050 mpu(Wire);
unsigned long t1;

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  mpu.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }  
  display.clearDisplay();
  display.display();
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
  
  t1 = millis();
}

void loop() {
  mpu.update();
  
  if ((millis() - t1) > 100) {
    display.clearDisplay();

    int x = display.width()/2 + 300.0 * sin(toRad(mpu.getAngleX()));
    int y = display.height()/2 + 300.0 * sin(toRad(mpu.getAngleY()));

    display.drawCircle(display.width()/2, display.height()/2, 30, SSD1306_WHITE);
    display.drawCircle(display.width()/2, display.height()/2, 6, SSD1306_WHITE);
    display.fillCircle(x,y, 3, SSD1306_INVERSE);

    //yaw
    int px = display.width()/2 + 30.0 * sin(toRad(mpu.getAngleZ()));
    int py = display.height()/2 + 30.0 * cos(toRad(mpu.getAngleZ()));
    display.fillCircle(px,py, 2, SSD1306_INVERSE);
    
    display.display();
    t1 = millis();
  }   
}

float toRad(float ang) {
  return (ang * PI)/180.0;
}

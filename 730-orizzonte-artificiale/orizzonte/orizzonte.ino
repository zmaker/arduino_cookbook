#include "Wire.h"
#include <MPU6050_light.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

MPU6050 mpu(Wire);

unsigned long t1;

int xc = display.width() / 2;
int yc = display.height() / 2;

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

}

void loop() {
  mpu.update();

  if ((millis() - t1) > 100) {
    display.clearDisplay();

    float roll = toRad(mpu.getAngleX());
    float pitch = toRad(mpu.getAngleY());

    int xh = xc + 100.0 * sin(roll);

    int x1 = xh + 30.0 * cos(pitch+PI/2);
    int y1 = yc + 30.0 * sin(pitch+PI/2);
    int x2 = xh - 30.0 * cos(pitch+PI/2);
    int y2 = yc - 30.0 * sin(pitch+PI/2);

    display.drawLine(x1,y1, x2,y2, SSD1306_WHITE);
    display.drawCircle(xc, yc, 30, SSD1306_WHITE);
    
    display.display();
    t1 = millis(); 
  }
}

float toRad(float ang) {
  return (ang * PI) / 180.0;  
}

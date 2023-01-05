//Teoria: 
//https://www.settorezero.com/wordpress/cosa-sono-come-funzionano-e-a-cosa-servono-gli-accelerometri/#Roll_Pitch_e_Yaw

#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  accelgyro.initialize();

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }  
  display.clearDisplay();
  display.display();
}

unsigned long t1;

void loop() {
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    float pitch = accToAngle(ay, ax, az);
    float roll = accToAngle(ax, ay, az);

    if ((millis() - t1) > 100) {
      display.clearDisplay();

      int x = display.width()/2 + 300.0 * sin(toRad(roll));
      int y = display.height()/2 + 300.0 * sin(toRad(pitch));
      
      display.drawCircle(display.width()/2, display.height()/2, 30, SSD1306_WHITE);
      display.drawCircle(display.width()/2, display.height()/2, 6, SSD1306_WHITE);
      display.fillCircle(x,y, 3, SSD1306_INVERSE);
      display.display();
      t1 = millis();
    }    
}

float toRad(float ang) {
  return (ang * PI)/180.0;
}

float accToAngle(float a, float b, float c){
  float d = sqrt(a*a + c*c);
  float ang = atan2(b, d);
  ang = (ang * 180.0)/ PI;
  return ang;
}

//Teoria: 
//https://www.settorezero.com/wordpress/cosa-sono-come-funzionano-e-a-cosa-servono-gli-accelerometri/#Roll_Pitch_e_Yaw

#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  accelgyro.initialize();
}

void loop() {
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    float pitch = accToAngle(ay, ax, az);
    float roll = accToAngle(ax, ay, az);

    Serial.print("Pitch: "); Serial.print(pitch);
    Serial.print("\tRoll: "); Serial.print(roll);
    Serial.print("\n");
}

float accToAngle(float a, float b, float c){
  float d = sqrt(a*a + c*c);
  float ang = atan2(b, d);
  ang = (ang * 180.0)/ PI;
  return ang;
}

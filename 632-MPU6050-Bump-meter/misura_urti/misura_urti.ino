/* ============================================
https://github.com/electroniccats/mpu6050

*/

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro(0x68);

// uncomment "OUTPUT_BINARY_ACCELGYRO" to send all 6 axes of data as 16-bit
// binary, one right after the other. This is very fast (as fast as possible
// without compression or data loss), and easy to parse, but impossible to read
// for a human.
//#define OUTPUT_BINARY_ACCELGYRO
#define OUTPUT_READABLE_ACCELGYRO

void setup() {
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  
  Wire.begin();
  Serial.begin(9600);

  accelgyro.initialize();

  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  // use the code below to change accel/gyro offset values
  /*
  Serial.println("Updating internal sensor offsets...");
  // -76	-2359	1688	0	0	0
  Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
  Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
  Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
  Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
  Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
  Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
  Serial.print("\n");
  accelgyro.setXGyroOffset(220);
  accelgyro.setYGyroOffset(76);
  accelgyro.setZGyroOffset(-85);
  Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
  Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
  Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
  Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
  Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
  Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
  Serial.print("\n");
  */
}

int ax, ay, az;
float x, y, z;
float magn, pmagn, bump;

void loop() {
    // read raw accel/gyro measurements from device
    accelgyro.getAcceleration(&ax, &ay, &az);
    x = ((float)ax) / 100.0;
    y = ((float)ay) / 100.0;
    z = ((float)az) / 100.0;
    magn = sqrt(x*x + y*y + z*z);

    bump = abs(magn - pmagn);    
    int level = (bump/15.0);
    Serial.print(magn); Serial.print("\t");
    Serial.print(level); Serial.println(" ");

    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    if (level > 1) digitalWrite(5, HIGH);
    if (level > 5) digitalWrite(6, HIGH);
    if (level > 10) digitalWrite(7, HIGH);
    if (level > 20) digitalWrite(8, HIGH);
    
    pmagn = magn;

/*    Serial.print(x); Serial.print("\t");
    Serial.print(y); Serial.print("\t");
    Serial.print(z); Serial.print("\t");
    Serial.print(magn); Serial.println(" ");
    */

  delay(100);
}

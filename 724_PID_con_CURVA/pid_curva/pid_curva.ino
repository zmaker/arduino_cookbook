#include <Adafruit_MAX31865.h>
// Use software SPI: CS, DI, DO, CLK
//Adafruit_MAX31865 thermo = Adafruit_MAX31865(10, 11, 12, 13);
// use hardware SPI, just pass in the CS pin
Adafruit_MAX31865 thermo = Adafruit_MAX31865(10);
// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      430.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0


#include <PID_v1.h>
double setpoint, input, output;
double kp=4, ki=2, kd=1;

PID myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);

enum stati {riscalda, mantieni, raffredda} stato;

uint32_t t1, t2;

void setup() {
  Serial.begin(9600);
  thermo.begin(MAX31865_2WIRE); 

  pinMode(3, OUTPUT);
  pinMode(9, OUTPUT);

  myPID.SetOutputLimits(0, 255);
  myPID.SetMode(AUTOMATIC);

  setpoint = thermo.temperature(RNOMINAL, RREF);
  setpoint = 15;
}

void loop() {
  input = thermo.temperature(RNOMINAL, RREF);
  myPID.Compute();
  analogWrite(9, output);
  analogWrite(3, output);

  switch (stato) {
    case riscalda:
      if ((millis() - t1) > 5000) {
        if (setpoint < 40.0) {
          setpoint += 1.0;
        } else {
          setpoint = 40.0;
          stato = mantieni;
        }
        t1 = millis();
      }
      break;
    case mantieni:
      
      break;
    case raffredda:

      break;
  }

  if ((millis() - t2) > 1000) {
    Serial.print("o:");Serial.print(output);
    Serial.print(",i:");Serial.print(input);
    Serial.print(",s:");Serial.print(setpoint);
    Serial.print("\n");
    t2 = millis();
  }
}

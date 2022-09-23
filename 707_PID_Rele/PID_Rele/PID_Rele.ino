#include <Adafruit_MAX31865.h>
#include <PID_v1.h>

// Use software SPI: CS, DI, DO, CLK
//Adafruit_MAX31865 thermo = Adafruit_MAX31865(10, 11, 12, 13);
// use hardware SPI, just pass in the CS pin
Adafruit_MAX31865 thermo = Adafruit_MAX31865(10);

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      430.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0

double ki=20, kp=3, kd=1;
double ingresso, uscita, setpoint;
int winsize = 5000;
unsigned long winstart;

PID pid(&ingresso, &uscita, &setpoint, kp, ki, kd, DIRECT);

void setup() {
  pinMode(6, OUTPUT);
  Serial.begin(9600);
  thermo.begin(MAX31865_2WIRE);  // set to 3WIRE or 4WIRE as necessary
  setpoint = 35.0;
  pid.SetOutputLimits(0, winsize);
  pid.SetMode(AUTOMATIC);
}

void loop() {
  ingresso = thermo.temperature(RNOMINAL, RREF);
  Serial.print("s: "); Serial.print(setpoint); Serial.print("\tt: ");Serial.println(ingresso);
  pid.Compute();

  if ((millis() - winstart) > winsize) {
    winstart += winsize;
  }
  if (uscita < (millis() - winstart)) {
    digitalWrite(6, LOW);
  } else {
    digitalWrite(6, HIGH);
  }
  delay(200);
}

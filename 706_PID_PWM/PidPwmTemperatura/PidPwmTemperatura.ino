#include <OneWire.h>
#include <DS18B20.h>

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DS18B20 sensor(&oneWire);

#include <PID_v1.h>
double Setpoint, Input, Output;
double kp = 100, ki=5, kd=1;

PID myPID(&Input, &Output, &Setpoint, kp, ki, kd, DIRECT);

void setup() {
  Serial.begin(9600);
  sensor.begin();
  sensor.requestTemperatures();
  while (!sensor.isConversionComplete()){}
  Input = sensor.getTempC();

  Serial.print("Tini: ");Serial.println(Input);
  
  pinMode(6, OUTPUT);

  Setpoint = 40;
  myPID.SetOutputLimits(0, 255);
  myPID.SetMode(AUTOMATIC);

}

void loop() {
  if (sensor.isConversionComplete()){
    Input = sensor.getTempC();      
    sensor.requestTemperatures();
  }
  
  myPID.Compute();
  
  Serial.print("O: ");Serial.print(Output);Serial.print("\tT: ");Serial.println(Input);
  analogWrite(6, Output);
  
  delay(1000);
}

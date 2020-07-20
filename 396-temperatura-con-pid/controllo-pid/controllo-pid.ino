#include <PID_v1.h>

#include <OneWire.h>
#include <DallasTemperature.h>

double setpoint, input, output;
double Kp=30, Ki=1, Kd=1;
unsigned long pidtime = 1000;

PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

OneWire oneWire(8);
DallasTemperature temp(&oneWire);

unsigned long t1; 

void setup() {
  pinMode(6, OUTPUT);
  temp.begin();
  Serial.begin( 9600 );

  myPID.SetSampleTime(pidtime);
  myPID.SetOutputLimits(0, 255);
  myPID.SetMode(AUTOMATIC);
}

void loop() {  
  
  if ((millis() - t1) > pidtime) { 
    temp.requestTemperatures();
    input = temp.getTempCByIndex(0);
    
    //QUI Aggiungo il PID
    //1. imposto il suo setpoint
    setpoint = 31.0;
    //2. calcolo i suoi valori di output assegnando la temp misurata
    myPID.Compute();
    //3. applico il controllo
    int pwm = constrain((int)output, 0, 255);
    analogWrite(6, pwm);

    Serial.print("in: ");
    Serial.print(input);
    Serial.print("\tout: ");
    Serial.print(output);
    Serial.print("\tpwm: ");
    Serial.println(pwm);

    t1 = millis();
  }
}

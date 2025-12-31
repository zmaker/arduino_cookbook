//https://github.com/Martinsos/arduino-lib-hc-sr04
#include <HCSR04.h>

UltraSonicDistanceSensor distanceSensor(6, 7); //Tr, Ec

float x_est = 0; //stima iniziale
float P = 1; //incertezza stima

float Q = 0.05;
float R = 4;

void setup() {
  Serial.begin(9600);

}

void loop() {
  float dist = distanceSensor.measureDistanceCm();

  if ((dist > 2) && (dist < 200)) {
    float kout = kalman(dist);
    Serial.print(dist);
    Serial.print(",");
    Serial.print(kout);
    Serial.println(",0,200");
  } else {
    Serial.println("0,0,0,200");
  }
  
  delay(100);

}

float kalman(float misura){
  float x_pred = x_est;
  float P_pred = P + Q;

  float K = P_pred / (P_pred + R);
  x_est = x_pred + K * (misura - x_pred);
  P = (1-K) * P_pred;

  return x_est;
}
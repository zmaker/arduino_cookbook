/*
 * https://github.com/F4GOJ/AD9850
 * 
 */

#include <AD9850.h>

const int W_CLK_PIN = 6;
const int FQ_UD_PIN = 7;
const int DATA_PIN = 8;
const int RESET_PIN = 9;

double freq = 1000;
double trimFreq = 124999500;

int phase = 0;

void setup(){
  DDS.begin(W_CLK_PIN, FQ_UD_PIN, DATA_PIN, RESET_PIN);
  DDS.calibrate(trimFreq);
  DDS.up();

  DDS.setfreq(freq, phase);
  
  /*delay(10000);
  DDS.down();
  delay(3000);
  DDS.up();
  delay(2000);
  DDS.setfreq(freq + 500, phase);
  delay(5000);
  DDS.down();
  */
}

void loop(){
  freq += 100;
  DDS.setfreq(freq, phase);
  delay(100);
  if (freq >= 10000) freq = 0;  
}

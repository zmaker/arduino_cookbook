#include "arduinoFFT.h"

#define SAMPLES 128
#define SAMPLING_FREQUENCY 1000

arduinoFFT FFT = arduinoFFT();

unsigned int sampling_period_us;
unsigned long microseconds;

double vReal[SAMPLES];
double vImag[SAMPLES];

void setup() {
  Serial.begin(115200);
  sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));
}

void loop() {
  for (int i = 0; i < SAMPLES; i++) {
      microseconds = micros();
      vReal[i] = analogRead(A0);
      vImag[i] = 0;
      while(micros() < (microseconds + sampling_period_us)){};  
  }
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
  double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
  //Serial.println(peak);

  for (int i = 0; i < SAMPLES/2; i++) {
    Serial.println(vReal[i], 1);
  }
  while(1);
  
}

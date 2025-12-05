#include "arduinoFFT.h"

#define SAMPLES 128             // numero di campioni (potenza di 2)
#define SAMPLING_FREQUENCY 9000 // Hz (deve essere > 2 * 3000 per Nyquist)

double vReal[SAMPLES];
double vImag[SAMPLES];

ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);

unsigned int sampling_period_us;
unsigned long microseconds;

void setup(){
  pinMode(3, OUTPUT);
  sampling_period_us = round(1000000.0 / SAMPLING_FREQUENCY);
}

void loop() {
  /* ====== Acquisizione campioni ====== */
  for (int i = 0; i < SAMPLES; i++) {
    microseconds = micros(); // tempo attuale

    vReal[i] = analogRead(A0); // campione dal microfono
    vImag[i] = 0;

    while (micros() < (microseconds + sampling_period_us)) {
      // attesa per mantenere frequenza costante
    }
  }

  /* ====== FFT ====== */
  FFT.windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.complexToMagnitude(vReal, vImag, SAMPLES);

  double resolution = (1.0 * SAMPLING_FREQUENCY) / SAMPLES; // Hz per bin
  int targetBin = round(3000.0 / resolution);
  double magnitude = vReal[targetBin];

  /* ====== Controllo LED PWM ====== */
  // Normalizziamo la magnitudine in range 0-255
  int pwm = constrain( map((int)magnitude, 20, 200, 0, 255) , 0,255);
  analogWrite(3, pwm);
  delay(10);
}

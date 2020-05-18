#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "arduinoFFT.h"

Adafruit_SSD1306 display(128, 32, &Wire, 4);
arduinoFFT FFT = arduinoFFT();

const uint16_t samples = 64;

double vReal[samples];
double vImag[samples];

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
      for(;;);
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  for (int i = 0; i < samples; i++) {
    vReal[0] = analogRead(A0); 
    vImag[0] = 0;
  }

  FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, samples, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, samples);

  double peak = FFT.MajorPeak(vReal, samples, 5000);

  display.clearDisplay();
  for (int i = 0; i < samples/2; i++){
     int y = map(vReal[i], 0, 1024, 0, 32);
     int xg = i*4;
     display.fillRect(xg, 32-y, 3, y, WHITE);
  }
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(32, 0);
  display.print(String(peak));
  display.display();
}

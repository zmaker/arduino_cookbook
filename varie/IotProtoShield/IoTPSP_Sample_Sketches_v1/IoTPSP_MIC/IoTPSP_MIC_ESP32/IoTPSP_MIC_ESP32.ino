// program to test a module on the IoT Proto Shield Plus
// www.gtronicsShop.com

// select ESP32 mini board: tools->Board->"WEMOS D1 MINI ESP32"
// select port number
 

/****************************************
  Example Sound Level Sketch for the
  Microphone Module
****************************************/
#define MIC_PIN 39



const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned long sample;

void setup()
{
  Serial.begin(9600);
}


void loop()
{
  unsigned long startMillis = millis(); // Start of sample window
  unsigned long peakToPeak = 0;   // peak-to-peak level

  unsigned long signalMax = 0;
  unsigned long signalMin = 4096;

  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(MIC_PIN);
    if (sample < 4096)  // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample;  // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample;  // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude

  Serial.println(peakToPeak);
}

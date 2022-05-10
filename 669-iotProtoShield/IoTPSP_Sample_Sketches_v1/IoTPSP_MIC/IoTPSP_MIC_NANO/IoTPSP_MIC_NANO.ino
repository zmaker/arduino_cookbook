// program to test a microphone module on the IoT Proto Shield Plus
// www.gtronicsShop.com


// select ARDUINO NANO or EVERY according to the device your are using
// tools->Board->"ARDUINO NANO xxxx"
// select port number
 

/****************************************
  Example Sound Level Sketch for the
  Microphone Module
****************************************/
#define MIC_PIN A7

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

void setup()
{
  Serial.begin(9600);
}


void loop()
{
  unsigned long startMillis = millis(); // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024; //4096; //1024;

  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(MIC_PIN);
    if (sample < 1024)  // toss out spurious readings
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

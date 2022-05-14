// program to test a microphone module on the IoT Proto Shield Plus
// www.gtronicsShop.com

// select ESP8266 mini board: tools->Board->"Lolin(Wemos) D1 R2 & Mini"
// select port number


/*ESP8266 pinout names and GPIOs
 * 
 * GPIO  PIN NAME  NOTES
 * ADC0  A0
 * 0   D3      BOOT FAILURE if PULLED LOW
 * 1   TX      BOOT FAILURE if PULLED LOW
 * 2   D4      BOOT FAILURE if PULLED LOW
 * 3   RX
 * 4   D2      also used as I2C SDA
 * 5   D1      also used as I2C SCL
 * 12    D6      High On BOOT. also used as SPI MISO
 * 13    D7      High On BOOT, also used as SPI MOSI
 * 14    D5      SPI SCLK
 * 15    D8      BOOT FAILURE if PULLED HIGH, also used as SPI CS
 * 16    D0      High On BOOT, also used to Wake device from deep sleep
 * 
 * 
 * */
  
/****************************************
  Example Sound Level Sketch for the
  Microphone Module
****************************************/
#define MIC_PIN A0



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

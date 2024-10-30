#include <MQUnifiedsensor.h>

#define CALIBRAZIONE 0

/************************Hardware Related Macros************************************/
#define         Board                   ("Arduino UNO")
#define         Pin                     (A0)  //Analog input 3 of your arduino
/***********************Software Related Macros************************************/
#define         Type                    ("MQ-3") //MQ3
#define         Voltage_Resolution      (5)
#define         ADC_Bit_Resolution      (10) // For arduino UNO/MEGA/NANO
#define         RatioMQ3CleanAir        (60) //RS / R0 = 60 ppm 
/*****************************Globals***********************************************/

MQUnifiedsensor MQ3(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void bar(Adafruit_SSD1306 &d, float val);

void setup() {
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.setTextSize(2); 
  display.setTextColor(SSD1306_WHITE);
  display.cp437(true);       
  display.clearDisplay();

  MQ3.setRegressionMethod(1);
  /*
    Exponential regression:
  Gas    | a      | b
  LPG    | 44771  | -3.245
  CH4    | 2*10^31| 19.01
  CO     | 521853 | -3.821
  Alcohol| 0.3934 | -1.504
  Benzene| 4.8387 | -2.68
  Hexane | 7585.3 | -2.849
  */
  MQ3.setA(0.3934);
  MQ3.setB(-1.504);
  MQ3.init();
  MQ3.setRL(1.5);

  float calcR0 = 0.42;
  if (CALIBRAZIONE) {
    Serial.print("Calibrating please wait.");
    for(int i = 1; i<=10; i ++) {
      MQ3.update(); // Update data, the arduino will read the voltage from the analog pin
      calcR0 += MQ3.calibrate(RatioMQ3CleanAir);
      Serial.print(".");
    }
    Serial.println(calcR0);
    Serial.println("  done!.");
  }
  MQ3.setR0(calcR0/10);

  if(isinf(calcR0)) {Serial.println("Warning: Conection issue, R0 is infinite (Open circuit detected) please check your wiring and supply"); while(1);}
  if(calcR0 == 0){Serial.println("Warning: Conection issue found, R0 is zero (Analog pin shorts to ground) please check your wiring and supply"); while(1);}

  display.setCursor(0,0);
  display.print("ETILOMETRO");
  display.display();
  delay(1000);
}

void loop() {
  MQ3.update();
  float ppm = MQ3.readSensor();
  
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("ppm: ");
  display.print(ppm);
  bar(display, ppm);
  display.display();

  delay(1000);
}

void bar(Adafruit_SSD1306 &d, float val){
  d.drawRect(0,17, 128, 15, SSD1306_WHITE);
  int vi = (int)(val * 100.0f);
  int w = map(vi, 0, 12, 0, 128);
  d.fillRect(0,17, w, 15, SSD1306_WHITE);
}

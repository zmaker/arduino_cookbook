#include <Adafruit_MAX31865.h>
#include <PID_v1.h>

// Use software SPI: CS, DI, DO, CLK
//Adafruit_MAX31865 thermo = Adafruit_MAX31865(10, 11, 12, 13);
// use hardware SPI, just pass in the CS pin
Adafruit_MAX31865 thermo = Adafruit_MAX31865(10);

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      430.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0

double ki=20, kp=3, kd=1;
double ingresso, uscita, setpoint;

PID pid(&ingresso, &uscita, &setpoint, kp, ki, kd, DIRECT);

//DISPLAY
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     4 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long t1;

void setup() {
  pinMode(6, OUTPUT);
  Serial.begin(9600);
  thermo.begin(MAX31865_2WIRE);  // set to 3WIRE or 4WIRE as necessary
  setpoint = 35.0;
  pid.SetOutputLimits(0, 255);
  pid.SetMode(AUTOMATIC);

  if(!oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  oled.setTextSize(1);      // Normal 1:1 pixel scale
  oled.setTextColor(SSD1306_WHITE); // Draw white text
  oled.cp437(true); 
  oled.clearDisplay();
}

void loop() {
  ingresso = thermo.temperature(RNOMINAL, RREF);
  //Serial.print("s: "); Serial.print(setpoint); Serial.print("\tt: ");Serial.println(ingresso);
  pid.Compute();

  analogWrite(6, (int)uscita);
  if ((millis() - t1) > 300) {
    oled.clearDisplay();
    oled.setCursor(0,0); 
    oled.print(F("T:"));
    oled.print(ingresso);    
    oled.print(" / ");
    oled.print(setpoint);
    
    oled.setCursor(0,10); 
    oled.print(F("KI     KP     KD"));
    oled.setCursor(0,20); 
    oled.print((int)ki);
    oled.setCursor(40,20); 
    oled.print((int)kp);
    oled.setCursor(80,20); 
    oled.print((int)kd);
    oled.display();
    
    
    //pid.SetTunings(ki,kp,kd);     

    t1 = millis();
  }
    
}

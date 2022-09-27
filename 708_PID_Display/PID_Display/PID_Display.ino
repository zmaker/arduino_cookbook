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

double kp=20, ki=3, kd=1;
double ingresso, uscita, setpoint;

PID pid(&ingresso, &uscita, &setpoint, kp, ki, kd, DIRECT);

//DISPLAY
#include "HD44780_LCD_PCF8574.h"
HD44780LCD lcd(2, 16, 0x27);
char str[17];

int bts, btp, btm, pv_bts, pv_btp, pv_btm;
int menu, prev_menu;
char opmode[] = {'R', 'T',  'P', 'I', 'D'};
double inc;

unsigned long t1;

void setup() {
  Serial.begin(9600);

  pinMode(9, OUTPUT); //PWM
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);

  thermo.begin(MAX31865_2WIRE);  // set to 3WIRE or 4WIRE as necessary
  setpoint = 35.0;
  pid.SetOutputLimits(0, 255);
  pid.SetMode(AUTOMATIC);

  lcd.PCF8574_LCDInit(LCDCursorTypeOff);
  lcd.PCF8574_LCDClearScreen();
  lcd.PCF8574_LCDBackLightSet(true);
  lcd.PCF8574_LCDGOTO(1, 0); 
  lcd.PCF8574_LCDSendString("PID"); 
  delay(1000);    

  Serial.println("PID mod");
}

void loop() {
  bts = digitalRead(4);  
  btp = digitalRead(5);
  btm = digitalRead(6);

  ingresso = thermo.temperature(RNOMINAL, RREF);
  //Serial.print("s: "); Serial.print(setpoint); Serial.print("\tt: ");Serial.println(ingresso);
  pid.Compute();

  analogWrite(9, (int)uscita);

  //menu e display
  //run, modki, modkp, modkd, modt
  if (!pv_bts && bts) { //FDS
    menu++;
    if (menu > 4) menu = 0;
    //Serial.println(menu);
  }

  if (!pv_btp && btp) { //FDS
    inc = 1.0;    
  }
  if (!pv_btm && btm) { //FDS
    inc = -1.0;    
  }
  
  switch (menu) {
    case 1:      
      setpoint = constrain(setpoint+inc, 15, 100);
      break;
    case 2:
      kp = constrain(kp+inc, 0, 100);
      break;
    case 3:
      ki = constrain(ki+inc, 0, 100);
      break;
    case 4:
      kd = constrain(kd+inc, 0, 100);
      break;
  }
  inc = 0;

  if ((menu == 0) && (prev_menu == 4)) {
    //restart pid
    pid.SetTunings(kp,ki,kd);       
  }

  if ((millis() - t1) > 250) {
    lcd.PCF8574_LCDGOTO(1, 0);
    sprintf(str, "t:%d", ((int)ingresso) );    
    lcd.PCF8574_LCDSendString(str);     

    lcd.PCF8574_LCDGOTO(1, 7);
    sprintf(str, "s:%d", ((int)setpoint) );    
    lcd.PCF8574_LCDSendString(str);      

    lcd.PCF8574_LCDGOTO(2, 0);
    sprintf(str, "p:%d", ((int)kp) );    
    lcd.PCF8574_LCDSendString(str);     

    lcd.PCF8574_LCDGOTO(2, 6);
    sprintf(str, "i:%d", ((int)ki) );    
    lcd.PCF8574_LCDSendString(str);      
    
    lcd.PCF8574_LCDGOTO(2, 11);
    sprintf(str, "d:%d", ((int)kd) );    
    lcd.PCF8574_LCDSendString(str);      

    //modalità
    lcd.PCF8574_LCDGOTO(1, 15);
    sprintf(str, "%c", opmode[menu] ); 
    lcd.PCF8574_LCDSendString(str);       

    t1 = millis();
  }
   
  pv_bts = bts;
  pv_btp = btp;
  pv_btm = btm;
  prev_menu = menu;
}

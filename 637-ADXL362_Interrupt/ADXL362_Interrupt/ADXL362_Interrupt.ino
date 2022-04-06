/*
 ADXL362
 
 for Analog Devices ADXL362 - Micropower 3-axis accelerometer
 go to http://www.analog.com/ADXL362 for datasheet
 
 SCL -> 13 Arduino
 SDA -> 11
 SDO -> 12
 CS  -> 10

 library: https://github.com/annem/ADXL362 
*/
#include <avr/sleep.h>
#include <avr/power.h>

#include <SPI.h>
#include <ADXL362.h>

ADXL362 xl;

void wakeUpNow() { // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP    (i.e. after getting interrupt)
  // execute code here after wake-up before returning to the loop() function  
  // timers and code using timers (serial.print and more...) will not work here.  
  // we don't really need to execute any special functions here, since we  
  // just want the thing to wake up 
  
  // precautionary while we do other stuff
  detachInterrupt(digitalPinToInterrupt(2));
  
  /*delay(500);
  Serial.println("WOKEN UP !!!!!!!!!!");
  delay(500);
 */
}

void setup() {
  pinMode(2, INPUT); 
  pinMode(8, OUTPUT); 
  xl.begin(); 
  Serial.begin(9600);
  delay(1000);

  //  Setup Activity and Inactivity thresholds
  //     tweaking these values will effect the "responsiveness" and "delay" of the interrupt function
  //     my settings result in a very rapid, sensitive, on-off switch, with a 2 second delay to sleep when motion stops
  xl.setupDCActivityInterrupt(300, 10);    // 300 code activity threshold.  With default ODR = 100Hz, time threshold of 10 results in 0.1 second time threshold
  xl.setupDCInactivityInterrupt(80, 30);   // 80 code inactivity threshold.  With default ODR = 100Hz, time threshold of 30 results in 2 second time threshold
  /* Other possible settings
  //  Motion activated On - stays on for 60 seconds 
  xl.setupDCActivityInterrupt(300, 10);    // 300 code activity threshold.  With default ODR = 100Hz, time threshold of 10 results in 0.1 second time threshold
  xl.setupDCInactivityInterrupt(80, 6000);  // 80 code inactivity threshold.  With default ODR = 100Hz, time threshold of 60000 results in 60 second time threshold
  */
  // Setup ADXL362 for proper autosleep mode
  // Map Awake status to Interrupt 1
  // *** create a function to map interrupts... coming soon
  xl.SPIwriteOneRegister(0x2A, 0x40);   
  //xl.SPIwriteOneRegister(0x2B, 0x40);   

  // Setup Activity/Inactivity register
  xl.SPIwriteOneRegister(0x27, 0x3F); // Referenced Activity, Referenced Inactivity, Loop Mode  
      
  // turn on Autosleep bit
  byte POWER_CTL_reg = xl.SPIreadOneRegister(0x2D);
  POWER_CTL_reg = POWER_CTL_reg | (0x04);       // turn on POWER_CTL[2] - Autosleep bit
  xl.SPIwriteOneRegister(0x2D, POWER_CTL_reg);
 
  xl.beginMeasure();                      // DO LAST! enable measurement mode   
  xl.checkAllControlRegs();               // check some setup conditions    
  delay(100);
  Serial.println("\nADXL362 - INT");
}

void sleepNow() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here  
  sleep_enable(); // enables the sleep bit in the mcucr register  
  attachInterrupt(digitalPinToInterrupt(2), wakeUpNow, RISING); // use interrupt 0 (pin 2) and run function  
  sleep_mode(); // here the device is actually put to sleep...!!

  sleep_disable(); // first thing after waking from sleep: disable sl¯eep...  
  power_all_enable();
}

void loop() {  
  if (digitalRead(2)) {
    // if ADXL362 is awake, report XYZT data to Serial Monitor
    delay(10);
    digitalWrite(8, HIGH);    // Turn on LED as visual indicator of awake
    //xl.readXYZTData(XValue, YValue, ZValue, Temperature); 
  } else {
    Serial.print("\nADXL went to sleep - Put Arduino to sleep now \n");
    digitalWrite(8, LOW);    // Turn off LED as visual indicator of asleep
    delay(100);
    sleepNow(); // sleep function called here
  }
}

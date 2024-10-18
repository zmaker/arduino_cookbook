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

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(100);

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

  /*****************************  MQ CAlibration ********************************************/ 
  // Explanation: 
   // In this routine the sensor will measure the resistance of the sensor supposedly before being pre-heated
  // and on clean air (Calibration conditions), setting up R0 value.
  // We recomend executing this routine only on setup in laboratory conditions.
  // This routine does not need to be executed on each restart, you can load your R0 value from eeprom.
  // Acknowledgements: https://jayconsystems.com/blog/understanding-a-gas-sensor
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

}

void loop() {
  MQ3.update();
  float ppm = MQ3.readSensor();
  Serial.print("Alcool: ");Serial.print(ppm);Serial.println(" ppm");
  delay(500);
}

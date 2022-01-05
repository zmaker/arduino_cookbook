/**
 * https://github.com/rocketscream/Low-Power
 * 
 * https://circuitdigest.com/microcontroller-projects/arduino-sleep-modes-and-how-to-use-them-to-reduce-power-consumption
 * 
 * https://circuitdigest.com/fullimage?i=inlineimages/u1/Six-Sleep-modes-in-ATmega328P.png
 * 
 // ATmega328P, ATmega168
  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
                SPI_OFF, USART0_OFF, TWI_OFF);

  // ATmega32U4
  //LowPower.idle(SLEEP_8S, ADC_OFF, TIMER4_OFF, TIMER3_OFF, TIMER1_OFF, 
  //     TIMER0_OFF, SPI_OFF, USART1_OFF, TWI_OFF, USB_OFF);

  // ATmega2560
  //LowPower.idle(SLEEP_8S, ADC_OFF, TIMER5_OFF, TIMER4_OFF, TIMER3_OFF, 
  //      TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART3_OFF, 
  //      USART2_OFF, USART1_OFF, USART0_OFF, TWI_OFF);

  // ATmega256RFR2
  //LowPower.idle(SLEEP_8S, ADC_OFF, TIMER5_OFF, TIMER4_OFF, TIMER3_OFF, 
  //      TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF,
  //      USART1_OFF, USART0_OFF, TWI_OFF);
 */

#include "LowPower.h"

void setup() {
  pinMode(4, OUTPUT);
}

void loop() {
  //LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  //delay(500);
  digitalWrite(4, HIGH);
  delay(500);
  digitalWrite(4, LOW);
}

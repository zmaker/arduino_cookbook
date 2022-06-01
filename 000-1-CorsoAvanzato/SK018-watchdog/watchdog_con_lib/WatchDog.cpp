/*===================================================================================================================================*
 
    @file     WatchDog.cpp
    @author   Nadav Matalon
    @license  MIT (c) 2016 Nadav Matalon

    WatchDog Timer Functionality

    Ver. 1.0.0 - First release (17.11.16)
    Ver. 1.1.0 - Added user-definible overflow period (18.11.16)
    Ver. 1.2.0 - Added compatibility for ATtiny441/841 (5.12.16)

 *===================================================================================================================================*
    LICENSE
 *===================================================================================================================================*
 
    The MIT License (MIT)
    Copyright (c) 2016 Nadav Matalon

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
    documentation files (the "Software"), to deal in the Software without restriction, including without
    limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
    the Software, and to permit persons to whom the Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial
    portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
    LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 
 *===================================================================================================================================*/

#if 1
__asm volatile ("nop");
#endif

#include "WatchDog.h"

WatchDog Wdog1;                                                             // preinstatiate for watcdog ISR function implementation

ovf_period_t WatchDog::ovfPeriod;                                           // class variable for storing the ovf period
volatile unsigned int WatchDog::ovfTop = 0;                                 // class variable for storing overflow counter top
volatile unsigned int WatchDog::ovfCounter = 0;                             // class variable for storing number of overflows

/*===================================================================================================================================*
    INITIALIZE (DEFAULT OVERFLOW PERIOD & DEFAULT STATUS)
 *===================================================================================================================================*/
//  ISR PARAMS:    User-Defined Function Name for WatchDog Timer ISR (without parentheses)

void WatchDog::init(void (*isrFunc)()) {
    WatchDog::setPeriod(OVF_1000MS);                                        // set overflow period to library default (1000mS)
    WatchDog::start();                                                      // start the watchdog timer
    Wdog1.attachInterrupt(isrFunc);                                         // activate user-defined interrupt service routine
}

/*===================================================================================================================================*
    INITIALIZE (PRE-DEFINED OVERFLOW PERIOD & DEFAULT STATUS)
 *===================================================================================================================================*/
//  ISR PARAMS:    User-Defined Function Name for WatchDog Timer ISR (without parentheses)
//  PERIOD PARAMS: OVF_16MS  / OVF_32MS   / OVF_64MS   / OVF_125MS  / OVF_250MS /
//                 OVF_500MS / OVF_1000MS / OVF_2000MS / OVF_4000MS / OVF_8000MS

void WatchDog::init(void (*isrFunc)(), ovf_period_t OvfPeriod) {
    WatchDog::setPeriod(OvfPeriod);                                         // set overflow period to one of the pre-defined values
    WatchDog::start();                                                      // start the watchdog timer
    Wdog1.attachInterrupt(isrFunc);                                         // activate user-defined interrupt service routine
}

/*===================================================================================================================================*
    INITIALIZE (DEFAULT OVERFLOW PERIOD & PRE-DEFINED STATUS)
 *===================================================================================================================================*/
//  ISR PARAMS:    User-Defined Function Name for WatchDog Timer ISR (without parentheses)
//  STATUS PARAMS: STOP / START

void WatchDog::init(void (*isrFunc)(), ovf_status_t OvfStatus) {
    WatchDog::setPeriod(OVF_1000MS);                                        // set overflow period to default (1000mS)
    OvfStatus ? WatchDog::start() : WatchDog::stop();                       // start or stop the watchdog timer
    Wdog1.attachInterrupt(isrFunc);                                         // activate user-defined interrupt service routine
}

/*===================================================================================================================================*
    INITIALIZE (USER-DEFINED OVERFLOW PERIOD & DEFAULT STATUS)
 *===================================================================================================================================*/
//  ISR PARAMS:    User-Defined Function Name for WatchDog Timer ISR (without parentheses)
//  CUSTOM VALUE:  Value must be divisible by one of the watchdog base pre-scaler values (i.e. 16 / 32 / 64 / 125 / etc.)

void WatchDog::init(void (*isrFunc)(), unsigned int CustomPeriod) {
    WatchDog::setPeriod(CustomPeriod);                                       // set overflow period to user-defined value (if valid)
    if (WatchDog::ovfPeriod) WatchDog::start();                              // start watchdog timer if custom value is valid
    Wdog1.attachInterrupt(isrFunc);                                          // setup user-defined interrupt service routine
}

/*===================================================================================================================================*
    INITIALIZE (PRE-DEFINED OVERFLOW PERIOD & PRE-DEFINED STATUS)
 *===================================================================================================================================*/
//  ISR PARAMS:    User-Defined Function Name for WatchDog Timer ISR (without parentheses)
//  PERIOD PARAMS: OVF_16MS  / OVF_32MS   / OVF_64MS   / OVF_125MS  / OVF_250MS /
//                 OVF_500MS / OVF_1000MS / OVF_2000MS / OVF_4000MS / OVF_8000MS
//  STATUS PARAMS: STOP / START
//  CUSTOM VALUE:  Value must be divisible by one of the watchdog base pre-scaler values (i.e. 16 / 32 / 64 / 125 / etc.)

void WatchDog::init(void (*isrFunc)(), ovf_period_t OvfPeriod, ovf_status_t OvfStatus) {
    WatchDog::setPeriod(OvfPeriod);                                         // set overflow period to one of the pre-defined values
    OvfStatus ? WatchDog::start() : WatchDog::stop();                       // start or stop watchdog timer
    Wdog1.attachInterrupt(isrFunc);                                         // activate user-defined interrupt service routine
}

/*===================================================================================================================================*
    INITIALIZE (USER-DEFINED OVERFLOW PERIOD & PRE-DEFINED STATUS)
 *===================================================================================================================================*/
//  ISR PARAMS:    User-Defined Function Name for WatchDog Timer ISR (without parentheses)
//  STATUS PARAMS: STOP / START
//  CUSTOM VALUE:  Value must be divisible by one of the watchdog base pre-scaler values (i.e. 16 / 32 / 64 / 125 / etc.)

void WatchDog::init(void (*isrFunc)(), unsigned int CustomPeriod, ovf_status_t OvfStatus) {
    WatchDog::setPeriod(CustomPeriod);                                      // set overflow period to user-defined value (if valid)
    if (OvfStatus && WatchDog::ovfPeriod) WatchDog::start();                // start watchdog timer if custom value is valid
    Wdog1.attachInterrupt(isrFunc);                                         // activate user-defined interrupt service routine
}

/*===================================================================================================================================*
    START WATCHDOG TIMER
 *===================================================================================================================================*/

void WatchDog::start() {
#if defined(__AVR_ATtiny841__)                                              // if using ATtiny841...
    noInterrupts();                                                         // disable global interrupts (cli)
        bitClear(MCUSR, WDRF);                                              // clear WDRF to enable clearing of WDE
        CCP = 0xD8;                                                         // write 'change enable' signature to Config Change Protection register
        WDTCSR = WatchDog::ovfPeriod;                                       // turn on WatchDog timer
    interrupts();                                                           // enable global interrupts (sei)
#else                                                                       // for all other AVRs...
    noInterrupts();                                                         // disable global interrupts (cli)
        bitClear(MCUSR, WDRF);                                              // clear WDRF to enable clearing of WDE
        WDTCSR = (1 << WDCE) | (1 << WDE);                                  // set relevant bits to enter watchdog timer configuration mode
        WDTCSR = WatchDog::ovfPeriod;                                       // turn on WatchDog timer
    interrupts();                                                           // enable global interrupts (sei)
#endif
}

/*===================================================================================================================================*
    STOP WATCHDOG TIMER
 *===================================================================================================================================*/

void WatchDog::stop() {
#if defined(__AVR_ATtiny841__)                                              // if using ATtiny841...
    noInterrupts();                                                         // disable global interrupts (cli)
        bitClear(MCUSR, WDRF);                                              // clear WDRF to enable clearing of WDE
        CCP = 0xD8;                                                         // write 'change enable' signature to Config Change Protection register
        WDTCSR = 0;                                                         // turn off WatchDog timer
    interrupts();                                                           // enable global interrupts (sei)
#else                                                                       // for all other AVRs...
    noInterrupts();                                                         // disable global interrupts (cli)
        bitClear(MCUSR, WDRF);                                              // clear WDRF to enable clearing of WDE
        WDTCSR = (1 << WDCE) | (1 << WDE);                                  // set relevant bits to enter watchdog timer configuration mode
        WDTCSR = 0;                                                         // turn off WatchDog timer
    interrupts();                                                           // enable global interrupts (sei)
#endif
}

/*===================================================================================================================================*
    WATCHDOG STATUS (0 = STOPPED / 1 = RUNNING)
 *===================================================================================================================================*/

byte WatchDog::status() {
    return (WDTCSR ? 1 : 0);                                                // watchdog timer status
}

/*===================================================================================================================================*
    GET WATCHDOG OVERFLOW PERIOD (in mS)
 *===================================================================================================================================*/

unsigned int WatchDog::getPeriod() {
    switch (WatchDog::ovfPeriod) {
        case (OVF_16MS)  : return   16 * (ovfTop + 1); break;
        case (OVF_32MS)  : return   32 * (ovfTop + 1); break;
        case (OVF_64MS)  : return   64 * (ovfTop + 1); break;
        case (OVF_125MS) : return  125 * (ovfTop + 1); break;
        case (OVF_250MS) : return  250 * (ovfTop + 1); break;
        case (OVF_500MS) : return  500 * (ovfTop + 1); break;
        case (OVF_1000MS): return 1000 * (ovfTop + 1); break;
        case (OVF_2000MS): return 2000 * (ovfTop + 1); break;
        case (OVF_4000MS): return 4000 * (ovfTop + 1); break;
        case (OVF_8000MS): return 8000 * (ovfTop + 1); break;
        default: return 0; break;                                           // return 0 if overflow period is not defined
    }
}

/*===================================================================================================================================*
    SET WATCHDOG OVERFLOW PERIOD (PRE-DEFINED VALUE, in mS)
    //  PARAMS: OVF_16MS   / OVF_32MS   / OVF_64MS   / OVF_125MS  / OVF_250MS /
    //          OVF_500MS  / OVF_1000MS / OVF_2000MS / OVF_4000MS / OVF_8000MS
 *===================================================================================================================================*/

void WatchDog::setPeriod(ovf_period_t newPeriod) {
    byte status = WatchDog::status();
    WatchDog::ovfPeriod = newPeriod;                                        // update new overflow period value
    status ? WatchDog::start() : WatchDog::stop();                          // start or stop timer based on state prior to change
}

/*===================================================================================================================================*
    SET WATCHDOG OVERFLOW PERIOD (USER-DEFINED VALUE, in mS)
 *===================================================================================================================================*/

void WatchDog::setPeriod(unsigned int customPeriod) {
    if      (customPeriod % 8000 == 0) { ovfTop = (customPeriod / 8000) - 1; WatchDog::setPeriod(OVF_8000MS); }
    else if (customPeriod % 4000 == 0) { ovfTop = (customPeriod / 4000) - 1; WatchDog::setPeriod(OVF_4000MS); }
    else if (customPeriod % 2000 == 0) { ovfTop = (customPeriod / 2000) - 1; WatchDog::setPeriod(OVF_2000MS); }
    else if (customPeriod % 1000 == 0) { ovfTop = (customPeriod / 1000) - 1; WatchDog::setPeriod(OVF_1000MS); }
    else if (customPeriod %  500 == 0) { ovfTop = (customPeriod /  500) - 1; WatchDog::setPeriod(OVF_500MS);  }
    else if (customPeriod %  250 == 0) { ovfTop = (customPeriod /  250) - 1; WatchDog::setPeriod(OVF_250MS);  }
    else if (customPeriod %  125 == 0) { ovfTop = (customPeriod /  125) - 1; WatchDog::setPeriod(OVF_125MS);  }
    else if (customPeriod %   64 == 0) { ovfTop = (customPeriod /   64) - 1; WatchDog::setPeriod(OVF_64MS);   }
    else if (customPeriod %   32 == 0) { ovfTop = (customPeriod /   32) - 1; WatchDog::setPeriod(OVF_32MS);   }
    else if (customPeriod %   16 == 0) { ovfTop = (customPeriod /   16) - 1; WatchDog::setPeriod(OVF_16MS);   }
    else WatchDog::stop();         // set 'ovfPeriod' to 0 & stop watchdog if requested value is not divisable by 16mS
}

/*===================================================================================================================================*
    CHECK VALIDITY OF OVERFLOW PERIOD VALUE
 *===================================================================================================================================*/

byte WatchDog::checkPeriod(unsigned int periodValue) {
    return ((periodValue % 16 == 0)   || (periodValue % 32 == 0)  || (periodValue % 64 == 0)   || (periodValue % 125 == 0)  ||
            (periodValue % 250 == 0)  || (periodValue % 500 == 0) || (periodValue % 1000 == 0) || (periodValue % 2000 == 0) ||
            (periodValue % 4000 == 0) || (periodValue % 8000 == 0));
}

/*===================================================================================================================================*
    USER-DEFINED WATCHDOG OVERFLOW INTERRUPT SERVICE ROUTINE FUNCTIONS
 *===================================================================================================================================*/

void WatchDog::attachInterrupt(void (*isr)()) {
    isrCallback = isr;
}

void WatchDog::attachInterrupt(void (*isr)(), ovf_period_t selectedPeriod) {
    attachInterrupt(isr);
}

void (*WatchDog::isrCallback)() = WatchDog::isrDefaultUnused;

void WatchDog::isrDefaultUnused() {}

/*===================================================================================================================================*
    BUILT-IN WATCHDOG INTERRUPT SERVICE ROUTINE
 *===================================================================================================================================*/

ISR(WDT_vect) {
    if (WatchDog::ovfCounter < WatchDog::ovfTop) {
        WatchDog::ovfCounter++;
    } else {
        WatchDog::ovfCounter = 0;
        Wdog1.isrCallback();
    }
}


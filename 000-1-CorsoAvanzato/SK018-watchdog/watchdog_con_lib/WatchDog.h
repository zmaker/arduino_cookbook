/*==============================================================================================================*

    @file     WatchDog.h
    @author   Nadav Matalon
    @license  MIT (c) 2016 Nadav Matalon

    WatchDog Timer Functions

    Ver. 1.0.0 - First release (17.11.16)
    Ver. 1.1.0 - Added user-definible overflow period (18.11.16)
    Ver. 1.2.0 - Added support for ATtiny441/841 (5.12.16)
 
 *===============================================================================================================*
    INTRODUCTION
 *===============================================================================================================*

    Many AVR's include an 'Enhanced Watchdog Timer' (WDT) which runs independently on a separate on-chip 128KHz oscilliator.
    The Watchdog Timer is typically used for pre-defined system reset duties (i.e. as a fail-safe or protection mechanism 
    against system crashes). However, given that it has its own interrupt vector, the WatchDog Timer may also be used 
    as a regular (albeit relatively restricted) time counter for managing a user-defined Interrupt Service Routine (ISR).

    Taking advantage of the above characteristics of the WatchDog Timer, the present light-weight library contains a small 
    collection of functions for controlling this Timer in its capacity as an interrupt generator. In other words, the user 
    can select the overflow period (in mS) of the timer, as well as compose the content of the ISR (Interrupt Service Routine) 
    which is set to run on each overflow event (e.g. getting a sensor reading every 500mS or blinking a LED at the rate of 
    once per second).

    Importantly, behind the scenes, the 'reset' capabilities of the WatchDog timer are entirely disabled by the library, 
    leaving only the overflow time-counting mechanism and corresponding interrupt service routine to run as they normally do.
    Hence, no system reset is preformed when using any of the library's functions.

    It is also worth mentioning that in order to keep the memory footprint of the library to a minimum, no objects are 
    instantiated during its operation and only one variable is stored in the system (namely: the timer's selected 
    overflow period).

    For more details about the WatchDog Timer, see the ATmega328P Datasheet:
    http://www.atmel.com/Images/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_datasheet.pdf

 *===============================================================================================================*
    BUG REPORTS
 *===============================================================================================================*

    Please report any bugs/issues/suggestions at the Github Repo of this library at: 
    https://github.com/nadavmatalon/WatchDog
 
 *===============================================================================================================*
    LICENSE
 *===============================================================================================================*

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

 *==============================================================================================================*/

#if 1
__asm volatile ("nop");
#endif

#ifndef WatchDog_h
#define WatchDog_h

#if !defined(ARDUINO_ARCH_AVR)
#error The WatchDog library only supports AVR processors
#endif

#include <Arduino.h>

namespace Watchdog {
                            //    7        6         5         4        3        2          1          0
    typedef enum:byte {     //   WDIF     WDIE     WDP[3]     WDCE     WDE     WDP[2]     WDP[1]     WDP[0]
        OVF_16MS   = 64,    //    0        1         0         0        0        0          0          0
        OVF_32MS   = 65,    //    0        1         0         0        0        0          0          1
        OVF_64MS   = 66,    //    0        1         0         0        0        0          1          0
        OVF_125MS  = 67,    //    0        1         0         0        0        0          1          1
        OVF_250MS  = 68,    //    0        1         0         0        0        0          0          0
        OVF_500MS  = 69,    //    0        1         0         0        0        1          0          0
        OVF_1000MS = 70,    //    0        1         0         0        0        1          0          1
        OVF_2000MS = 71,    //    0        1         0         0        0        1          1          1
        OVF_4000MS = 96,    //    0        1         1         0        0        0          0          0
        OVF_8000MS = 97     //    0        1         1         0        0        0          0          1
    } ovf_period_t;

    typedef enum:byte {
        STOP  = 0,
        START = 1
    } ovf_status_t;

    class WatchDog {
        public:
            static void init(void (*isrFunc)());
            static void init(void (*isrFunc)(), ovf_period_t OvfPeriod);
            static void init(void (*isrFunc)(), ovf_status_t OvfStatus);
            static void init(void (*isrFunc)(), unsigned int CustomPeriod);
            static void init(void (*isrFunc)(), ovf_period_t OvfPeriod, ovf_status_t OvfStatus);
            static void init(void (*isrFunc)(), unsigned int CustomPeriod, ovf_status_t OvfStatus);
            static void start();
            static void stop();
            static byte status();
            static unsigned int getPeriod();
            static void setPeriod(ovf_period_t newPeriod);
            static void setPeriod(unsigned int customPeriod);
            static byte checkPeriod(unsigned int periodValue);
            void   attachInterrupt(void (*isr)());
            void   attachInterrupt(void (*isr)(), ovf_period_t selectedPeriod);
            static void (*isrCallback)();
            static void isrDefaultUnused();
            static volatile unsigned int ovfTop;
            static volatile unsigned int ovfCounter;
        private:
            static ovf_period_t ovfPeriod;
    };
}

using namespace Watchdog;

extern WatchDog Wdog1;

#endif

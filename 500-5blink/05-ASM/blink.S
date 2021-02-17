; Blink LED on PB5(Arduino Uno pin 13)
; http://forum.arduino.cc/index.php?topic=159572#msg1194604

#define __SFR_OFFSET 0
 
#include "avr/io.h"

.global start
.global blink

start:
  sbi   DDRB,5  ; Set PB5 come output
  ret

blink:
  ldi   r20,250 ; imposta il delay in ms. Il Max value è 255.
  call  delay_n_ms
  sbi   PORTB,5 ; Attiva PB5
  ldi   r20,250
  call  delay_n_ms
  cbi   PORTB,5 ; Disattiva PB5
  ret

delay_n_ms:
  ; Delay about r20*1ms. Destroys r20, r30, and r31.
  ; One millisecond is about 16000 cycles at 16MHz.
  ; The basic loop takes about 5 cycles, so we need about 3000 loops.
  ldi   31, 3000>>8 ; high(3000)
  ldi   30, 3000&255  ; low(3000)
delaylp:
  sbiw    r30, 1
  brne    delaylp
  subi    r20, 1
  brne    delay_n_ms
  ret

# https://docs.micropython.org/en/latest/esp32/quickref.html

from machine import Pin, ADC, PWM
import time

pin3 = Pin(6)
adc = ADC(pin3, atten=ADC.ATTN_11DB)

pwm2 = PWM(Pin(5), freq=5000)

while True:
    val = adc.read_u16()
    volt = adc.read_uv() / 1000000
    print(f"valore: {val} \ttens: {volt} V")
    pwm2.duty_u16(val)
    
    time.sleep_ms(100)
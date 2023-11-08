from machine import Pin, PWM
import time 

pwm2 = PWM(Pin(5), freq=5000, duty_u16=32768)
f = pwm2.freq()
d = pwm2.duty()

print("freq: ", f, "duty: ", d)
print(pwm2)

while True:
    for i in range(0, 1024):
        pwm2.duty(i)
        time.sleep(.001)
    for i in range(1023, 0, -1):
        pwm2.duty(i)
        time.sleep(.001)
from machine import Pin, UART
import time

#pin 13
led = Pin(48, Pin.OUT)

uart = UART(1, 9600)
time.sleep(1)
print("uart ok")

n = 0
while True:
    st = n%2
    print(st)
    uart.write(str(st))
    led.value(st)
    
    n += 1
    time.sleep(1)
    received = uart.read()
    print(received)
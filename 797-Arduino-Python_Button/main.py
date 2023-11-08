from machine import Pin

#D3 -> 6
#D2 -> 5
p2 = Pin(5, Pin.IN, Pin.PULL_UP)
p3 = Pin(6, Pin.OUT, value=0)

while True:
    if p2.value() == 0:
        p3.on()
    else:
        p3.off()

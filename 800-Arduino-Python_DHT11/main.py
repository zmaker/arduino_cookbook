import dht
from machine import Pin
import time
 
#sensore su pin D4
sensor = dht.DHT11(Pin(7))
time.sleep(2)
 
while True:
    sensor.measure()
    t = sensor.temperature()
    h = sensor.humidity()
    print(f"t: {t}C\t h: {h}%")
    time.sleep(2)
  
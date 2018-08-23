import serial
import time

arduino = serial.Serial('/dev/cu.usbmodem1421',9600)
time.sleep(1)

print("pronto a ricevere")

while (True):
    print arduino.readline()
    time.sleep(.5)
 

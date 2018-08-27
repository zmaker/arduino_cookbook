import serial
import time

arduino = serial.Serial('/dev/cu.usbmodem1A1211', 9600)
time.sleep(1)

print("prnto a ricevere")

while (True):
    print arduino.readline()
    time.sleep(.5)

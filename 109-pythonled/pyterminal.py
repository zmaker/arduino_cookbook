import serial
import time

arduino = serial.Serial('/dev/cu.usbmodem1A1211', 9600)
time.sleep(1)

while (True):
    val = raw_input("comando: ")
    arduino.write(val)
    print(val)

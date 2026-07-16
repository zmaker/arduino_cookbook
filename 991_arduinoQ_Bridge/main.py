import time
from arduino.app_utils import *

def fromQRB(data: int):
  print("from arduino: ", data)

Bridge.provide("fromQRB", fromQRB)

c = 0

print("Python App - Main")

def loop():
    global c
    c += 1
    #print(c)
    Bridge.call("myfun", c)
    time.sleep(1)

# See: https://docs.arduino.cc/software/app-lab/tutorials/getting-started/#app-run
App.run(user_loop=loop)

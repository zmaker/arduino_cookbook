import time
from arduino.app_utils import App

print("Hello World")

def loop():
    time.sleep(10)

# See: https://docs.arduino.cc/software/app-lab/tutorials/getting-started/#app-run
App.run(user_loop=loop)

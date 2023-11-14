import network
import urequests
from time import sleep

wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect("reelco_2_4", "password")
print("connesso wifi")

while True:
    res = urequests.get("https://www.zeppelinmaker.it/helloworld.txt")
    print(res.text)
    sleep(2)
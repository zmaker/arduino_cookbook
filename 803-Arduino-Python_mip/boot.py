import mip
import network
 
wifi = network.WLAN(network.STA_IF)
wifi.active(True)
wifi.connect("reelco_2_4", "password")
print("WiFi: connesso...")
mip.install("https://raw.githubusercontent.com/tinypico/tinypico-micropython/master/lis3dh%20library/lis3dh.py");
print("ok")
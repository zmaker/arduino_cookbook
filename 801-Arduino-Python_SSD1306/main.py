 # Import the Pin class and SoftI2C class (for using I2C) form the machine module
from machine import I2C, Pin
import ssd1306
# Import the sleep_ms class from the time module
from time import sleep

# Set the display width to 128 pixels
DISPLAY_WIDTH = 128   
# Set the display height to 64 pixels
DISPLAY_HEIGHT = 64   

# Create a SoftI2C object for I2C communication with the specified pins and frequency
i2c = I2C(0, scl = Pin(12), sda = Pin(11), freq=200000)
#i2c = SoftI2C(scl=Pin(12), sda=Pin(11), freq=100000)   
#print(i2cbus)
#print(i2c)

# Create an SSD1306 OLED object with the specified width, height, and I2C bus
oled = ssd1306.SSD1306_I2C(DISPLAY_WIDTH, DISPLAY_HEIGHT, i2c, addr=0x3C)   

oled.fill(0)
oled.show()

count = 0

while True:
    #https://docs.micropython.org/en/latest/esp8266/tutorial/ssd1306.html
    oled.fill(0)
    oled.text("count: " + str(count), 10, 10)
    oled.line(0,20, count, 20, 1)
    oled.show()
    
    count += 1
    if count > 128:
        count = 0
    sleep(1)

    
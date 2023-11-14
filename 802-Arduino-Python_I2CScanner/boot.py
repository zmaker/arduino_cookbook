import machine
i2c = machine.I2C(scl=machine.Pin(12), sda=machine.Pin(11))
print("scan bus...")
device = i2c.scan()

if len(device) == 0:
    print("nessun dispositivo!")
else:
    print(f"Trovati {len(device)} device")
    i = 0
    for d in device:
        print(f"{i}: device con indirizzo {hex(d)}")
        i += 1

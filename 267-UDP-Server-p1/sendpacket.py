import socket

PORTNUM = 8888
IPADDR = '192.168.1.147'

print("Send UDP packet")

PACKETDATA = 'hello!'

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)

try: 
    s.connect((IPADDR, PORTNUM))    
    s.send(PACKETDATA)

except:
    print("errore invio")
    pass

s.close()

print("done")



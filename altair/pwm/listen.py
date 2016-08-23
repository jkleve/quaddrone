import serial
import struct

# original baud = 57600
port = serial.Serial('/dev/ttyUSB0', 38400, stopbits=1, timeout=5)

#print hex(0)

#port.write(hex(0))

#power = 48;
#data = struct.pack(hex(power))
#port.write(data)
while True:
    d = port.read(1)
    print d

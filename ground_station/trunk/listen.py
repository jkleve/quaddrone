import serial

# original baud = 57600
port = serial.Serial('/dev/ttyUSB0', 38400, stopbits=1, timeout=5)

port.write('1')

d = port.read(1)
print d

import serial
import struct

# original baud = 57600
port = serial.Serial(port='/dev/ttyUSB0', 
                     baudrate=38400,
                     bytesize=serial.EIGHTBITS,
                     parity=serial.PARITY_NONE,
                     stopbits=serial.STOPBITS_ONE, 
                     timeout=5)

#print hex(0)

#n = 42
#print type(n)
#print '{0:b}'.format(n)

i = (42).to_bytes(1, byteorder='little')
#print(isinstance(i, byte))
print(i)

port.write(i)
print(port.read(1))
'''
#power = 48;
n = 0
while True:
  data = struct.pack('!B',n)
  n += 1
  port.write(data)
  d = port.read(1)
  print d
  print '{0:b}'.format(int(d))
  print '----------------'
'''

#print int2bin(d)


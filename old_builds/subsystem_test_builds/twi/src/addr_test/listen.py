import serial
import struct

# original baud = 57600
#port = serial.Serial(port='/dev/ttyUSB0',
port = serial.Serial(port='/dev/ttyACM0', 
                     baudrate=38400,
                     bytesize=serial.EIGHTBITS,
                     parity=serial.PARITY_NONE,
                     stopbits=serial.STOPBITS_ONE, 
                     timeout=10)

while True:
    d = (port.read(1)).decode('utf-8')
    #d = (struct.unpack('b', raw)[0]).decode('utf-8')
    data = ''
    if (d == '{'):
        d = port.read(1).decode('utf-8')
        while (d != '}'):
            data += d
            d = port.read(1).decode('utf-8')
        print(data)
    else:    
        print('no start condition > %c' % d)

'''
data = struct.pack("b", 42)
port.write(data)

rec = port.read(1)
print rec
'''
#print hex(0)

#n = 42
#print type(n)
#print '{0:b}'.format(n)
'''
roll = 1
pitch = 4
yaw = 3
data = struct.pack("bbb", roll, pitch, yaw)
port.write(data)

(r, p, y) = struct.unpack("bbb", port.read(3))
print("roll: ", r, " pitch: ", p, " yaw: ", y)
'''



'''
i = (42).to_bytes(1, byteorder='little')
#print(isinstance(i, byte))
print(i)

port.write(i)
print(port.read(1))

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


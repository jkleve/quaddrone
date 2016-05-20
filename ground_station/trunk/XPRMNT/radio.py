#!/usr/bin env python
import time
import serial

def read():
    port = serial.Serial('COM3',38400, timeout=5)
    data = port.read(1)
    datum = str(data)
    print datum
    if datum == '0':
        print 'Connected to APM'
        port.write('hello')
        alpha = 'hello'
        print alpha.encode('hex')
       
            
    else:
        print 'Nothing found'

#!/usr/bin env python
import time
import serial

def read():
    port = serial.Serial('COM3',57600,stopbits=1, timeout=5)
    data = port.read(1)
    datum = str(data)
    print datum
    if datum == '0':
        print 'Connected to APM'
        port.write('a')
        time.sleep(1)
    else:
        #port.write('d')
        print 'Nothing Found'
'''
        while True:
            received = port.read(1)
            print str(received)
            if received == '0':
                print 'HEART'
            port.flushInput()
            time.sleep(.001)
'''        


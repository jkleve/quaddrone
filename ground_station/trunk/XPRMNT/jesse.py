import time, serial

def jesse():
    ser = serial.Serial('COM3',57600,stopbits=1, timeout= 5)
    data = ser.write('d')
    print data
    datum = str(data)
    print datum
    

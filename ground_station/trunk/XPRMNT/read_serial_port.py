import serial


#baud = input('Enter baud rate: ')
#port = input('Enter Port name: ')
baud = 57600
port ='COM4'
def serial_handler(baud,port):
    ser = serial.Serial(port,baud)
    print ser.name
    ser.read(10)
    ser.close()


serial_handler(baud,port)

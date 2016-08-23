import sys
import glob
import serial

cereal_port_count = 0
def cereal_ports():
    global cereal_port_count
    #Windows platform system
    if sys.platform.startswith('win'):
        ports = ['COM' + str(i+1) for i in range(256)]

    #Linux platform system
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        ports = glob.glob('/dev/tty[A-Za-z]*')
    #
    elif sys.platform.starswith('darwin'):
        ports = glob.glob('dev/tty.*')
    else:
        raise EnvironmentError('Unsuported system platform')

    result = []
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
    return result
    cereal_port_count = len(cereal_ports())
if __name__ == '__main__':
    serial_ports = cereal_ports()
    print serial_ports
        
    

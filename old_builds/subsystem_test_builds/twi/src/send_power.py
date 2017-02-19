#QuadDrone serial test
#6/14/16 (CAC)
#Dummy transmitter for output testing
import sys
import time
import serial
import struct
import time
from ctypes import *
from threading import Thread
from PyQt4 import QtGui,QtCore


#port = serial.Serial(port='/dev/ttyUSB0', 
port = serial.Serial(port='/dev/ttyACM4', 
                     baudrate=38400,
                     bytesize=serial.EIGHTBITS,
                     parity=serial.PARITY_NONE,
                     stopbits=serial.STOPBITS_ONE, 
                     timeout=2)
power = 0

class Widget(QtGui.QWidget):

    #Function that initializes ground station
    def __init__(window):
        super(Widget, window).__init__()
        window.initUI()

    #command window and most of the knick knacks
    #to be viewed in the GUI
    def initUI(window):
        window.col = QtGui.QColor(160,160,160)


        #Throttle
        window.progress_bar_t = QtGui.QProgressBar(window)
        window.progress_bar_t.setGeometry(50, 50, 125, 75)
        window.progress_bar_t.setOrientation(0x2)
        window.progress_bar_t.setValue(power)

        #Window Application Geometry
        window.setGeometry(300, 300, 250, 150)
        window.setWindowTitle('Motor Test')
        window.show()

    def keyPressEvent(window, eventQKeyEvent,setEnabled=False):
        #This function enables any type of the keys listed below to be mapped onto some movement
        #Basic mode is
        global power
        key = eventQKeyEvent.key()
        if key == 87:# w
                power += 1
                #power = min(power, 25) # limiting to 25 for UART issue
                power = min(power,100)
                window.progress_bar_t.setValue(power)
                write(window, power)
        elif key == 83:# s
                power -= 1
                power = max(power, 0)
                window.progress_bar_t.setValue(power)
                write(window, power)
        elif key == 85:# u
                power = 100
                window.progress_bar_t.setValue(power)
                write(window, power)
        elif key == 32:# space
                power = 0
                window.progress_bar_t.setValue(power)
                write(window, power)
        else:
                power = 0
                window.progress_bar_t.setValue(power)
                write(window, power)
                #eventQKeyEvent.ignore()

def write(window, val):
    #data = port.write(struct.pack('b', -1*val-1))
    data = port.write(struct.pack('b', val))
    print "sending %d" % val 
    #print "%d bytes written" % data

def listen():
    while True:
        d = port.read(1)
        if len(d) > 0:
            v = struct.unpack('b', d)[0]
            print "%s: received %d" % ( time.ctime(time.time()), v )

def main():

    app = QtGui.QApplication(sys.argv)
    ex = Widget()
    sys.exit(app.exec_())


if __name__ == '__main__':
    Thread(target=main).start()
    Thread(target=listen).start()

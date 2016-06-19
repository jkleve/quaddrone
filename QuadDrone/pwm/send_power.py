#QuadDrone serial test
#6/14/16 (CAC)
#Dummy transmitter for output testing
import sys
import time
import serial
from PyQt4 import QtGui,QtCore


com_port = '/dev/ttyUSB0' #Choose whatever comport to be used for serial
#port = serial.Serial('/dev/ttyUSB0', 38400, stopbits=1, timeout=5)
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
                power = min(power, 100)
                window.progress_bar_t.setValue(power)
                write(window,com_port,power)
        elif key == 83:# s
                power -= 1
                power = max(power, 0)
                window.progress_bar_t.setValue(power)
                write(window,com_port,power)
        elif key == 85:# u
                power = 100
                window.progress_bar_t.setValue(power)
                write(window,com_port,power)
        elif key == 32:# space
                power = 0
                window.progress_bar_t.setValue(power)
                write(window,com_port,power)
        else:
                power = 0
                window.progress_bar_t.setValue(power)
                write(window,com_port,power)
                #eventQKeyEvent.ignore()

def write(window,com_port,val):
    port = serial.Serial(com_port,38400,stopbits=1,timeout=5)
    data  = port.write(hex(val))


def main():

    app = QtGui.QApplication(sys.argv)
    ex = Widget()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()

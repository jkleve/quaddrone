# QuadDrone serial test
# 6/14/16 (CAC)
# Dummy transmitter for output testing

from ctypes import *
from errno import EACCES, EPERM
import logging
import serial
import struct
import sys
import time
from threading import Thread
from PyQt4 import QtGui, QtCore


# Create a new log level
MESSAGE_LOG_LEVEL = 25
# Add the newly created log level
logging.addLevelName(MESSAGE_LOG_LEVEL, "MESSAGE")
# Set the format for logging and set log level
logging.basicConfig(format='%(asctime)s %(levelname)s: %(message)s', datefmt='%H:%M:%S', level=logging.INFO)


def log_message(message):
    logging.log(MESSAGE_LOG_LEVEL, message)


connection = None
power = 0
exit_threads = False


class Widget(QtGui.QWidget):

    def __init__(window):
        """Function that initializes ground station"""
        super(Widget, window).__init__()

        window.col = QtGui.QColor(160, 160, 160)

        # Throttle
        window.progress_bar_t = QtGui.QProgressBar(window)
        window.progress_bar_t.setGeometry(50, 50, 125, 75)
        window.progress_bar_t.setOrientation(0x2)
        window.progress_bar_t.setValue(power)

        # Window Application Geometry
        window.setGeometry(300, 300, 250, 150)
        window.setWindowTitle('Motor Test')
        window.show()

    def keyPressEvent(window, eventQKeyEvent, setEnabled=False):
        """This function enables any type of the keys listed below to be mapped onto some movement
        Basic mode is
        """
        global power
        key = eventQKeyEvent.key()
        if key == 87:  # w
            power += 5
            # power = min(power, 25) # limiting to 25 for UART issue
            power = min(power, 100)
            print
            window.progress_bar_t.setValue(power)
            write(window, power)
        elif key == 83:  # s
            power -= 5
            power = max(power, 0)
            window.progress_bar_t.setValue(power)
            write(window, power)
        elif key == 85:  # u
            power = 100
            window.progress_bar_t.setValue(power)
            write(window, power)
        elif key == 32:  # space
            power = 0
            window.progress_bar_t.setValue(power)
            write(window, power)
        else:
            power = 0
            window.progress_bar_t.setValue(power)
            write(window, power)
            # eventQKeyEvent.ignore()


def write(window, val):
    data = connection.write(struct.pack('B', val))


def getChecksum(data):
    checksum = 0

    for d in data:
        checksum += d
        if checksum > 0xff:
            checksum = d % 0xff

    # Get inverse and convert to unsigned
    return ~checksum + 2**8


TWI_MESSAGES = dict([
        (0x08, 'Start sent'),
        (0x10, 'Repeated start sent'),
        (0x18, 'SLA+W transmitted, received ACK'),
        (0x20, 'SLA+W transmitted, received NACK'),
        (0x28, 'Data transmitted, received ACK'),
        (0x30, 'Data transmitted, received NACK'),
        (0x38, 'Arbitration lost in SLA+W or data bytes'),
        (0x40, 'SLA+R transmitted, received ACK'),
        (0x48, 'SLA+R transmitted, received NACK'),
        (0x50, 'Data received, transmitted ACK'),
        (0x58, 'Data received, transmitted NACK')
    ])


class Receiver:
    modes = {
        'string': 0xff,
        'twi_msg': 0xfe,
        'test': 0x48,
        'end': 0x00
    }

    _mode_to_string = {v: k for k, v in modes.items()}

    def __init__(self):
        pass

    def run(self):
        while not exit_threads:
            mode = self.hunting()
            if mode is None:  # We didn't get a mode, continue hunting
                pass
            elif hasattr(self, mode):
                data = self.get_data()
                if data is None:
                    logging.warning("Timed out while getting data in mode {}".format(mode))
                else:
                    getattr(self, mode)(data)
            else:
                logging.warning("Could not find mode {}".format(mode))

    # TODO add a checksum to packet
    def get_data(self):
        """
        Receive the data section of the packet
        :return: Data section of packet received. None if we timedout before 'end' was recieved
        """
        start = time.time()
        data = list()

        # Get data
        b = self.get_byte()
        while b != self.modes['end']:
            # Timeout after 5 milliseconds of looking for 'end'
            # Tested with the string 'Hello'. It took about 1.5 milliseconds to receive
            if time.time() - start > 0.005:
                return None
            data.append(b)
            b = self.get_byte()

        # Calculate and compare checksum

        return data

    def get_byte(self):
        d = connection.read(1)
        if len(d) > 0:
            return struct.unpack('B', d)[0]

    def test(self, data):
        print(data)

    def end(self, data):
        logging.info("Received null character")

    def start(self, data):
        logging.warning("Received start character but ended up here ...")

    def string(self, data):
        s = ''.join([chr(b) for b in data])
        log_message("(string) {}".format(s))

    def twi_msg(self, data):
        if len(data) > 1:
            log.warning("Received more than 1 byte in twi_msg mode")
        twi_mode = data[0]  # We should only have 1 byte
        log_message("(twi_msg) {}".format(TWI_MESSAGES[twi_mode]))

    def hunting(self):
        #while True:
        b = self.get_byte()
        if b in self.modes.values():
            return self._mode_to_string[b]
        else:
            return None


#def listen():
#    try:
#        while True:
#            d = connection.read(1)
#            if len(d) > 0:
#                v = struct.unpack('B', d)[0]
#                log_message("%s (%3d)" % (format(v, '#04x'), v))
#    except Exception:
#        logging.info("Disconnected. Device no longer available or double access.")


def gui():
    app = QtGui.QApplication(sys.argv)
    ex = Widget()
    sys.exit(app.exec_())



if __name__ == '__main__':
    ports = ['/dev/ttyACM0', '/dev/ttyACM1', '/dev/ttyACM2', '/dev/ttyUSB0']
    for port in ports:
        try:
            connection = serial.Serial(port=port,
                                       baudrate=38400,
                                       bytesize=serial.EIGHTBITS,
                                       parity=serial.PARITY_NONE,
                                       stopbits=serial.STOPBITS_ONE,
                                       timeout=2)
        except Exception as e:
            # Check if the exception was due to sudo permissions
            if e.errno == EPERM or e.errno == EACCES:
                logging.error("Need sudo permissions")
                break
        else:
            logging.info("Connected on {}".format(port))
            break

    if connection is None:
        logging.critical("Couldn't connect to device on any port")
        sys.exit(1)

    #Thread(target=gui).start()
    receiver = Receiver()
    listening_thread = Thread(target=receiver.run)
    listening_thread.start()

    try:
        while True:
            time.sleep(.1)
    except (KeyboardInterrupt, SystemExit):
        print("")  # Print a newline character
        logging.info("Caught keyboard interrupt")
        # Tell threads to exit
        exit_threads = True
        # Wait for threads to exit
        listening_thread.join()
        sys.exit(0)

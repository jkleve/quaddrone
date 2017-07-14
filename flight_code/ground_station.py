# QuadDrone serial test
# 6/14/16 (CAC)
# Dummy transmitter for output testing

from argparse import ArgumentParser
from collections import namedtuple
from ctypes import *
from errno import EACCES, EPERM
import logging
import serial
from serial.serialutil import SerialException
import struct
import sys
import time
from threading import Thread
from PyQt4 import QtGui, QtCore

Packet = namedtuple('Packet', 'mode data checksum valid')

# Create a new log level
MESSAGE_LOG_LEVEL = 25

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


def get_checksum(data):
    checksum = 0

    for d in data:
        checksum += d

    checksum = checksum % 0x100

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

REGISTERS = dict([
    (0x90, 'TCCR3A'),
    (0x91, 'TCCR3B'),
    (0x92, 'TCCR3C'),
    (0x94, 'TCNT3'),
    (0x96, 'ICR3'),
    (0x98, 'OCR3A'),
    (0x9A, 'OCR3B'),
    (0x9C, 'OCR3C'),
    (0xB8, 'TWBR'),
    (0xB9, 'TWSR'),
    (0xBC, 'TWCR'),
    (0x124, 'TCNT5')
])

CHECKSUM_LEN = 1
TWI_MSG_LEN = 1
REGISTER_LEN = 4
WORD_LEN = 2
BYTE_LEN = 1


class Receiver:
    modes = {
        'string': 0xff,
        'twi_msg': 0xfe,
        'register': 0xfd,
        'data': 0xfc,
        'word': 0xfb,
        'byte': 0xfa,
        'test': 0x48,
        'end': 0x00
    }

    _mode_to_string = {v: k for k, v in modes.items()}

    def __init__(self):
        self.num_bytes = 0
        self.mode = None

    def run(self):
        while not exit_threads:
            mode = self.hunting()
            if mode is None:  # We didn't get a header, continue hunting
                pass
            elif hasattr(self, mode):
                self.mode = mode  # TODO needed?
                getattr(self, mode)(self.modes[mode])
            else:
                logging.warning("Could not find mode {}".format(mode))

    def assemble_packet(self, header, data):
        """Create the Packet object and check the checksum
        header: the mode
        data: data and checksum. Checksum is the last byte
        """
        received_checksum = data[-1]
        data = data[0:-1]

        # Append header to front and calculate and compare checksum
        checksum = get_checksum([header] + data)

        if checksum != received_checksum:
            try:  # See if we can get the message type
                header_name = self._mode_to_string[header]
            except KeyError:
                header_name = "unknown ({})".format(str(header))

            # Get different forms of data
            data_hex = [hex(d) for d in data]
            data_str = [chr(d) for d in data]

            logging.warning("\n Received bad checksum (calculated {} != {})"
                            "\n with header {} and data {}"
                            "\n hex {}"
                            "\n str {}".format(checksum, received_checksum, header_name, data, data_hex, data_str))
            return Packet(header, data, checksum, False)

        return Packet(header, data, checksum, True)

    def get_data(self, size):
        """
        Receive the data section of the packet
        :return: Data section of packet received. None if we timeout before 'end' was received
        """
        start = time.time()
        data = list()

        # Add checksum size to number of bytes to receive
        size += CHECKSUM_LEN

        # Get data
        b = self.get_byte()
        data.append(b)
        size -= 1

        while size > 0:
            if time.time() - start > 0.010:
                logging.warning("Timed out while getting data in mode {}".format(self.mode))
                return None

            b = self.get_byte()
            data.append(b)
            size -= 1

        return data

    def get_byte(self):
        try:
            d = connection.read(1)
        except SerialException:
            logging.critical("")  # Add some extra emphasis
            logging.critical("Device disconnected. Exiting ...")

            global exit_threads
            exit_threads = True
            sys.exit(1)

        if len(d) > 0:
            self.num_bytes += 1
            b = struct.unpack('B', d)[0]  # TODO this may be assuming everything is unsigned
            # print("received {}".format(b))
            return b

    def test(self, header):
        print(self._mode_to_string[header])

    def end(self, header):
        logging.info("Received null character")

    def start(self, header):
        logging.warning("Received start character but ended up here ...")

    def string(self, header):
        str_len = self.get_byte()
        data = self.get_data(str_len)

        if data is None:  # Failure
            return

        data.insert(0, str_len)
        packet = self.assemble_packet(header, data)

        if packet.valid is False:  # Failure
            return

        data = packet.data[1:]  # Get the data, excluding the str_len
        s = ''.join([chr(b) for b in data])
        log_message("(string) {}".format(s))

    def register(self, header):
        data = self.get_data(REGISTER_LEN)

        if data is None:  # Failure
            return

        packet = self.assemble_packet(header, data)

        if packet.valid is False:  # Failure
            return

        data = packet.data
        if len(data) != REGISTER_LEN:
            logging.warning("\n Received unexpected number of bytes in register mode"
                            "\n {} instead of {} bytes".format(len(data), REGISTER_LEN))  # TODO +1 for length?

        value = (data[3] << 8) + data[2]
        register = (data[1] << 8) + data[0]

        try:
            register_name = REGISTERS[register]
        except KeyError:
            logging.warning("Register {} does not exist."
                            "Data in unknown register: {}".format(hex(register), value))
        else:
            log_message("(register {}) {} ({})".format(register_name, value, hex(value)))

    def twi_msg(self, header):
        data = self.get_data(TWI_MSG_LEN)

        if data is None:  # Failure
            return

        packet = self.assemble_packet(header, data)

        if packet.valid is False:  # Failure
            return

        data = packet.data
        if len(data) > TWI_MSG_LEN:
            logging.warning("Received more than {} data byte(s) in twi_msg mode".format(TWI_MSG_LEN))
        twi_mode = data[0]  # We should only have 1 byte
        try:
            log_message("(twi_msg) {}".format(TWI_MESSAGES[twi_mode]))
        except KeyError:
            logging.warning("Couldn't find TWI message {}".format(hex(twi_mode)))

    def data(self, header):
        num_bytes = self.get_byte()
        data = self.get_data(num_bytes)

        if data is None:  # Failure
            return

        data.insert(0, num_bytes)
        packet = self.assemble_packet(header, data)

        if packet.valid is False:  # Failure
            return

        data = [hex(d) for d in packet.data[1:]]  # Get the data, excluding the num_bytes
        log_message("(data) {}".format(data))

    def word(self, header):
        data = self.get_data(WORD_LEN)

        if data is None:  # Failure
            return

        packet = self.assemble_packet(header, data)

        if packet.valid is False:  # Failure
            return

        data = packet.data
        word = (data[1] << 8) + data[0]
        log_message("(word) {}".format(word))

    def byte(self, header):
        data = self.get_data(BYTE_LEN)

        if data is None:  # Failure
            return

        packet = self.assemble_packet(header, data)

        if packet.valid is False:  # Failure
            return

        data = packet.data
        log_message("(byte) {} ({})".format(data[0], hex(data[0])))

    def hunting(self):
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


def main():
    global connection
    global exit_threads

    timeout = 20  # Seconds
    start_time = time.time()
    ports = ['/dev/ttyACM0', '/dev/ttyACM1', '/dev/ttyACM2', '/dev/ttyUSB0']

    logging.info("Attempting to connect to device")
    while connection is None:
        if time.time() - start_time > timeout:
            logging.error("Timed out")
            break

        for port in ports:
            try:
                connection = serial.Serial(port=port,
                                           baudrate=38400,
                                           bytesize=serial.EIGHTBITS,
                                           parity=serial.PARITY_NONE,
                                           stopbits=serial.STOPBITS_ONE,
                                           timeout=2)  # This timeout is for if the port actually exists
            except Exception as e:
                # Check if the exception was due to sudo permissions
                if e.errno == EPERM or e.errno == EACCES:
                    logging.error("Need sudo permissions")
                    sys.exit(1)
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
            if exit_threads is True:
                break
    except (KeyboardInterrupt, SystemExit):
        print("")  # Print a newline character
        logging.info("Caught keyboard interrupt")
        # Tell threads to exit
        exit_threads = True
    finally:
        # Wait for threads to exit
        listening_thread.join()
        sys.exit(0)


if __name__ == '__main__':
    parser = ArgumentParser(description="Ground station for quadcopter flight code")
    parser.add_argument('-ms', action='store_true', help="Print time with milli-seconds")

    args = parser.parse_args()

    # Add the newly created log level
    logging.addLevelName(MESSAGE_LOG_LEVEL, "MESSAGE")
    # Set the format for logging and set log level
    if args.ms is True:
        logging.basicConfig(format='%(asctime)s.%(msecs)d %(levelname)s: %(message)s', datefmt='%H:%M:%S', level=logging.INFO)
    else:
        logging.basicConfig(format='%(asctime)s %(levelname)s: %(message)s', datefmt='%H:%M:%S', level=logging.INFO)

    # Run main function until we exit or catch an exception
    try:
        main()
    except (KeyboardInterrupt, SystemExit):
        logging.info("Exiting")
        sys.exit(0)

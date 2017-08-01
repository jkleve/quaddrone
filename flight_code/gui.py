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

UserInputState = namedtuple('UserInputState', 'yaw pitch roll throttle')


class UserInput:
    def __init__(self):
        self.yaw = 50
        self.pitch = 50
        self.roll = 50
        self.throttle = 0

    def get_state(self):
        return UserInputState(self.yaw, self.pitch, self.roll, self.throttle)


class Widget(QtGui.QWidget):

    def __init__(self):
        """Function that initializes ground station"""
        super(Widget, self).__init__()

        #self.col = QtGui.QColor(160, 160, 160)

        self.input = UserInput()

        # Throttle
        self.input.throttle = 0
        self.throttle_bar = QtGui.QProgressBar(self)
        self.throttle_bar.setGeometry(0, 0, 50, 75)
        self.throttle_bar.setOrientation(0x2)
        self.throttle_bar.setValue(self.input.throttle)

        #self.pitch = QtGui.QLabel(self)
        #self.pitch.setGeometry(0, 80, 50, 10)
        #self.pitch.setText(str(power))
        self.yaw_label = QtGui.QLabel(self)
        self.yaw_label.setGeometry(0, 100, 50, 10)
        self.yaw_label.setText("Yaw")

        self.input.yaw = 50
        self.yaw = QtGui.QProgressBar(self)
        self.yaw.setGeometry(0, 110, 75, 20)
        self.yaw.setOrientation(0x1)
        self.yaw.setValue(self.input.yaw)

        self.input.pitch = 50
        self.pitch = QtGui.QProgressBar(self)
        self.pitch.setGeometry(50, 0, 20, 75)
        self.pitch.setOrientation(0x2)
        self.pitch.setValue(self.input.pitch)

        self.input.roll = 50
        self.roll = QtGui.QProgressBar(self)
        self.roll.setGeometry(70, 30, 75, 20)
        self.roll.setOrientation(0x1)
        self.roll.setValue(self.input.roll)

        #self.test = QtGui.QDial(self)
        #self.test.setNotchesVisible(True)
        #self.test.setWrapping(False)

        # Window Application Geometry
        self.setGeometry(300, 300, 600, 500)
        self.setWindowTitle('Quadcopter Ground Station')
        self.show()

    def keyPressEvent(self, event):
        """This function enables any type of the keys listed below to be mapped onto some movement
        Basic mode is
        """
        key = event.key()

        # Yaw
        if key == ord('E'):
            self.set_yaw(100)
        elif key == ord('Q'):
            self.set_yaw(0)

        # Pitch
        elif key == ord('W'):
            self.set_pitch(100)
        elif key == ord('S'):
            self.set_pitch(0)

        # Roll
        elif key == ord('D'):
            self.set_roll(100)
        elif key == ord('A'):
            self.set_roll(0)

        # Throttle
        elif key == ord('K'):
            throttle = min(self.input.throttle + 1, 100)
            self.set_throttle(throttle)
            self.send(power)
        elif key == ord('J'):
            throttle = max(self.input.throttle - 1, 0)
            self.set_throttle(throttle)
        elif key == ord('U') or key == ord('L'):
            throttle = min(self.input.throttle + 5, 100)
            self.set_throttle(throttle)
        elif key == ord('H'):
            throttle = min(self.input.throttle - 5, 100)
            self.set_throttle(throttle)
        elif ord('9') >= key >= ord('0'):
            self.set_throttle(10*int(chr(key)))
        else:
            self.set_throttle(0)

    def keyReleaseEvent(self, event):
        key = event.key()

        # Yaw
        if key == ord('Q') or key == ord('E'):
            self.set_yaw(50)
        # Pitch
        elif key == ord('W') or key == ord('S'):
            self.set_pitch(50)
        # Roll
        elif key == ord('A') or key == ord('D'):
            self.set_roll(50)
        else:
            event.ignore()

    def set_yaw(self, yaw):
        self.yaw.setValue(yaw)
        self.input.yaw = yaw

    def set_pitch(self, pitch):
        self.pitch.setValue(pitch)
        self.input.pitch = pitch

    def set_roll(self, roll):
        self.roll.setValue(roll)
        self.input.roll = roll

    def set_throttle(self, throttle):
        self.throttle_bar.setValue(throttle)
        self.input.throttle = throttle

    @staticmethod
    def send(state):
        print("Sending {}".format(state))


def gui():
    import signal
    signal.signal(signal.SIGINT, signal.SIG_DFL)
    app = QtGui.QApplication(sys.argv)
    ex = Widget()
    sys.exit(app.exec_())


if __name__ == '__main__':
    gui()
    sys.exit()



import sys
from PyQt4 import QtGui, QtCore
import pygame
from pygame.locals import *

class Example(QtGui.QWidget):
    
    def __init__(self):
        super(Example, self).__init__()
        
        self.initUI()
        
    def initUI(self):      

        self.pbar = QtGui.QProgressBar(self)
        self.pbar.setGeometry(30, 40, 200, 25)

        self.btn = QtGui.QPushButton('Start', self)
        self.btn.move(40, 80)
        self.btn.clicked.connect(self.doAction)

        self.timer = QtCore.QBasicTimer()
        self.step = 0
        
        self.setGeometry(300, 300, 280, 170)
        self.setWindowTitle('QtGui.QProgressBar')
        self.show()
    def arrow_control(self):
        while True:
            r = pygame.event.wait()
            if (r.type == pygame.KEYDOWN):
                pressed = pygame.ket.get_pressed()
                if press == 1:
                    name = pygame.key.name()
                    if name == 'left':
                        print 'las'
                    elif name == 'right':
                        print 'pe'    
                    elif name == 'up':
                        print 'lo'
                    elif name == 'down':
                        print 'tas'

    def timerEvent(self, e):
      
        if self.step >= 100:
        
            self.timer.stop()
            self.btn.setText('Finished')
            return
            
        self.step = self.step + 1
        arrow_control()
        self.pbar.setValue(self.step)

    def doAction(self):
        if self.timer.isActive():
            self.timer.stop()
            self.btn.setText('Start')
            
        else:
            self.timer.start(100, self)
            self.btn.setText('Stop')
        
def main():
    
    app = QtGui.QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == '__main__':
    pygame.init()
    pygame.display.init()
    main()
    

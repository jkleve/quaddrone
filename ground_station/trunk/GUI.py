#!/usr/bin/env python

'''
This Ground Station Control will handle all messages to be sent to the Quadcopter
More deets on the way blah blah

################################################
'''
import sys
import time
import serial
from PyQt4 import QtGui,QtCore, QtOpenGL
from OpenGL import GL

######All modules created go here
import list_ports
import WASD
import joystick_handler
import joystick_drawer
import radio

######
print "############################################################"
print "#    This is GUIllermo : The quadcopter's ground station   #"        
print "#                     Version 0.0.2                        #"
print "############################################################"
print ''
        
com_port = 'COM3'

class Widget(QtGui.QWidget):
    
    #Function that initializes ground station
    def __init__(window):
        super(Widget, window).__init__()
        window.initUI()
        
    #Function that "pre-draws" (drawing is done in joystick_drawer.py)
    #command window and most of the knick knacks
    #to be viewed in the GUI    
    def initUI(window):
        window.col = QtGui.QColor(160,160,160)

        #Square for Connection Button                                           #Creates a background for the connection button to change colors
        window.square = QtGui.QFrame(window)                                    #We make a box or frame
        window.square.setGeometry(148,50,78,24)                                 #We move it and set its size like we want it
        window.square.setStyleSheet("QWidget { background-color: %s }" %        #Sets color and tells it what will be updated it 
              window.col.name())                      

        #Connection Button                                                      #The Connect Button is created
        connect_button = QtGui.QPushButton("Connect", window)                   #We make a label with some text over it
        connect_button.move(150,50)                                             #We move it where we want it
        connect_button.setCheckable(True)                                       #Sets the button to be toggable between two different mode
        connect_button.clicked[bool].connect(window.msg)                        #If the button is pressed msg() kicks in

        #Dropdown box for Port Listing                                                           #Here the Com Port DropDown box is handled
        window.lbl = QtGui.QLabel("No Com port selected",window)                #We make a label that tells us our current port
        window.lbl.move(250,50)                                                 #We move to where we want it
        com_port_drop_down = QtGui.QComboBox(window)                            #The Combo box is drawn
        serial_ports = list_ports.cereal_ports()                                #from the module list_ports.py we call its main function
        cereal_port_count = len(list_ports.cereal_ports())                      #Gives us the size of the tuple or count of objexts inside matrix
        for port_increment in range(cereal_port_count):                         #Depending on how many ports are open we create a space for each 
                com_port_drop_down.addItem(serial_ports[port_increment])        #Items are added inside the Combo box
        com_port_drop_down.move(250,75)                                         #We move the drop down where we want it
        com_port_drop_down.activated[str].connect(window.port_drop_activate)    #When activated, port_drop_activate() runs

        #Master Control Toggles########
        #WASD Control *To be determined if used
        cb1 = QtGui.QCheckBox('WASD Control On/Off', window)
        cb1.move(150,100)
        cb1.stateChanged.connect(window.change_title)
        #Joystick Control
        cb2 = QtGui.QCheckBox('Joystick Control On/Off', window)
        cb2.move(150,120)
        cb2.stateChanged.connect(window.joystick_control_mode)
        #Xbox 360 Controller Control
        cb3 = QtGui.QCheckBox('Xbox Controller Control On/Off', window)
        cb3.move(150,140)
        cb3.stateChanged.connect(window.xbox_control_mode)

        #Joystick Progress Bars########
        #X
        window.progress_bar_x = QtGui.QProgressBar(window)
        window.progress_bar_x.setGeometry(150, 160, 200, 25)
        window.progress_bar_x.setValue(50)
        #Y
        window.progress_bar_y = QtGui.QProgressBar(window)
        window.progress_bar_y.setGeometry(150, 180, 165, 25)
        window.progress_bar_y.setOrientation(0x2)
        window.progress_bar_y.setValue(50)
        #Z
        window.progress_bar_z = QtGui.QProgressBar(window)
        window.progress_bar_z.setGeometry(150, 200, 200, 25)
        window.progress_bar_z.setValue(50)
        #Throttle
        window.progress_bar_t = QtGui.QProgressBar(window)
        window.progress_bar_t.setGeometry(150, 220, 165, 25)
        window.progress_bar_t.setOrientation(0x2)
        window.progress_bar_t.setValue(50)
        #Window Application Geometry                                            #Geometry and surface of the main window is created
        window.setGeometry(0, 40, 2000, 950)                                    #Sets size for my Toshiba pc
        window.setWindowTitle('QuadCopter Ground Station Ver. 0.0.2')           #Sets the title of the GUI
        window.setWindowIcon(QtGui.QIcon('qd_icon.png'))                        #Sets the dope picture of the GUI, or just the icon  
        window.show()

###########################################################################################
####Drawing of Primary Flight Display is done here
####The PFD includes information about the desired QC's attitude and eventually
####the real attitude of the QC
        window.glWidget = GLWidget()
        pfd_box = QtGui.QHBoxLayout()
        pfd_box.addWidget(window.glWidget)
        window.setLayout(pfd_box)


        
    #Function that handles close event, in case of hitting wrong button
    def closeEvent(window, event):                                              #Handles the event when you try to quit the GUI while running
        reply = QtGui.QMessageBox.question(window, 'Wait up buddy!',            #Makes a prompt box
            "Are you sure to quit?", QtGui.QMessageBox.Yes |                    #Sets what both buttons in the prompt box are (yes /no)
            QtGui.QMessageBox.No, QtGui.QMessageBox.No)                         #
        if reply == QtGui.QMessageBox.Yes:                                      #If yes-then the program goes to hell
            event.accept()                                                      #If no or exit(the prompt box)-the event is ignored
        else:
            event.ignore()
    com_port = ''
    #Sends Connection message and alters connection_button 's color
    
    def msg(window, pressed):                                                   #Handles the Connection_button_box's color and prints the sent command
        if pressed:
                print 'Sent'
                window.col.setGreen(255)
                read(com_port,window)
        else:
                window.col.setGreen(160)

        window.square.setStyleSheet("QFrame { background-color: %s }" %
            window.col.name())
    #Activate com port
    def port_drop_activate(window,text):                                        #When port_lists.py is called whatever port was selected gets sent to           
        window.lbl.setText(text)                                                #                                                               here
        window.lbl.adjustSize()                                                 #Then the size of the label is rearanged so that all text can be seen at all times
        print "USB port %s selected" %text                                      #Just prints out what port is selected
        com_port = text
        return com_port
    

    #Master Control Toggler function
    def change_title(window,state):
            if state == QtCore.Qt.Checked:
                    print 'Master Control set to: WASD'
                    print '  Key | Control   '
                    print '  Q   |   Up      '
                    print '  W   |   FWD     '
                    print '  E   |   DWN     '
                    print '  A   |   ROLL L  '
                    print '  S   |   BCK     '
                    print '  D   |   ROLL R  '
                    print '  X   |   YAW L   '
                    print '  C   |   YAW R   '               
            else:
                    #nothing
                    print ''
                    
    def joystick_control_mode(window,state):
                    #Call joystick handler
            #print joystick_drawer.X
            if state == QtCore.Qt.Checked:
                    print "Master Control set to: Joystick"
                    joystick_handler.main(window,0)
               
            elif state == QtCore.Qt.Unchecked:
                    print "Joystick Control off"
                    joystick_handler.main(window,1)
                    window.progress_bar_x.setValue(50)      

    def xbox_control_mode(window,state):
                    #Call joystick handler
            #print joystick_drawer.X
            if state == QtCore.Qt.Checked:
                    print "Master Control set to: Xbox Controller"
                    joystick_handler.main(window,2)
               
            elif state == QtCore.Qt.Unchecked:
                    print "Xbox Controller Control off"
                    joystick_handler.main(window,1)
                    window.progress_bar_x.setValue(50)               
    #WASD Control function
    def keyPressEvent(window, eventQKeyEvent,setEnabled=False):
        key = eventQKeyEvent.key()
        if key == 87:
                print 'FORWARD'
                window.progress_bar_x.setValue()
        elif key == 65:
                print 'ROLL LEFT'
        elif key == 83:
                print 'BACK'
                window.progress_bar_x.setValue()
        elif key == 68:
                print 'ROLL RIGHT'
        elif key == 81:
                print 'UP'
        elif key == 69:
                print 'DOWN'
        elif key == 88:
                print 'YAW LEFT'
        elif key == 67:
                print 'YAW RIGHT'
        else:
                eventQKeyEvent.ignore()
                
def read(com_port,window):
        port  = serial.Serial(com_port,57600,stopbits=1,timeout=5)
        data  = port.read(1)
        datum = str(data)
        print datum
        if datum == '0':
            print 'Connected to APM'
            port.write('a')
            time.sleep(1)
        else:
            print 'Nothing Found'          


    

def paint_me_joy(window,axis_or_button,pstn):
    if axis_or_button <= 4:
            axis = axis_or_button
            if axis == 1:
                    X = pstn
                    window.progress_bar_x.setValue(X)
                    #Quad.pos.x = pstn/50
                    #print 'X is at: %.4f' % X
                    return X
            
            elif axis == 2:
                    Y = pstn
                    window.progress_bar_y.setValue(Y)
                    #Quad.pos.y = pstn/50
                    #print 'Y is at: %.4f' % Y
            elif axis == 3:
                    Throttle = pstn
                    window.progress_bar_t.setValue(Throttle)
                    print 'Throttle is at: %.4f' % Throttle
            elif axis == 4:
                    Z = pstn
                    window.progress_bar_z.setValue(Z)
                    #Quad.pos.z = pstn/50
                    #print 'Z is at: %.4f' % Z
    elif  (axis_or_button >=5 and  axis_or_button <= 16):
            button = axis_or_button
            if button == 5:
                    print 'Button pressed: Trigger'
            elif button == 6:
                    print 'Button pressed: 2'
            elif button == 7:
                    print 'Button pressed: 3'
            elif button == 8:
                    print 'Button pressed: 4'
            elif button == 9:
                    print 'Button pressed: 5'
            elif button == 10:
                    print 'Button pressed: 6'
            elif button == 11:
                    print 'Button pressed: 7'
            elif button == 12:
                    print 'Button pressed: 8'
            elif button == 13:
                    print 'Button pressed: 9'
            elif button == 14:
                    print 'Button pressed: 10'
            elif button == 15:
                    print 'Button pressed: 11'
            elif button == 16:
                    print 'Button pressed: 12'
                    
def paint_me_box(window,axis_or_button,pstn):
    if axis_or_button <= 4:
            axis = axis_or_button
            if axis == 1:
                    X = pstn
                    window.progress_bar_x.setValue(X)
                    #Quad.pos.x = pstn/50
                    #print 'X is at: %.4f' % X
                    return X
            
            elif axis == 2:
                    Y = pstn
                    window.progress_bar_y.setValue(Y)
                    #Quad.pos.y = pstn/50
                    #print 'Y is at: %.4f' % Y
            elif axis == 3:
                    Throttle = pstn
                    window.progress_bar_t.setValue(Throttle)
                    print 'Throttle is at: %.4f' % Throttle
            elif axis == 4:
                    Z = pstn
                    window.progress_bar_z.setValue(Z)
                    #Quad.pos.z = pstn/50
                    #print 'Z is at: %.4f' % Z
    elif  (axis_or_button >=5 and  axis_or_button <= 16):
            button = axis_or_button
            if button == 5:
                    print 'Button pressed: A'
            elif button == 6:
                    print 'Button pressed: B'
            elif button == 7:
                    print 'Button pressed: X'
            elif button == 8:
                    print 'Button pressed: Y'
            elif button == 9:
                    print 'Button pressed: LB'
            elif button == 10:
                    print 'Button pressed: RB'
            elif button == 11:
                    print 'Button pressed: Back'
            elif button == 12:
                    print 'Button pressed: Start'
            elif button == 13:
                    print 'Button pressed: LS'
            elif button == 14:
                    print 'Button pressed: RS'

class GLWidget(QtOpenGL.QGLWidget):
    roll_change  = QtCore.pyqtSignal(int)
    pitch_change = QtCore.pyqtSignal(int)
    
    def __init__(window, parent=None):
        super(GLWidget, window).__init__(parent)
        
        window.object = 0
        window.roll   = 0
        window.pitch  = 0
        window.lastPos = QtCore.QPoint()

    def set_roll(window, angle):
        if angle != window.roll:
            window.roll = angle
            window.roll_change.emit(angle)
            window.updateGL()

    def set_pitch(window, angle):
        if angle != window.pitch:
            window.pitch = angle
            window.pitch_change.emit(angle)
            window.updateGL()

    def initializeGL(window):
        window.object = window.makeObject()
        GL.glShadeModel(GLG.GL_FLAT)
        GL.glEnable(GL.GL_DEPTH_TEST)
        GL.glEnable(GL.GL_CULL_FACE)

    def paintGL(window):
        GL.glClear(GL.GL_COLOR_BUFFER_BIT | GL.GL_DEPTH_BUFFER_BIT)
        GL.glLoadIdentity()
        GL.glTranslated(0.0, window.pitch, 0.0)
        GL.glRotated(window.roll /16.0, 0.0, 1.0, 0.0)
        GL.glCallList(window.object)
        
    def makeObject(window):
        genList = GL.glGenLists(1)
        GL.glNewList(genList, GL.GL_COMPILE)

        GL.glBegin(GL.GL_QUADS)

        GL.glEnd()
        GL.glEndList()
        return genList

def main():
    
    app = QtGui.QApplication(sys.argv)
    ex = Widget()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()    



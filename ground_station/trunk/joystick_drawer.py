#!/usr/bin/env python

'''
Joystick Drawer- Once the state of all axes are given they come here
                 for further segregation into GUIllermo
'''
X        = 50
Y        = 50
Z        = 50
Throttle = 0
#axis = 0
def draw(axis_or_button, pstn):
    global X
    global Y
    global Z
    global Throttle
    #global axis
    if axis_or_button <= 4:
        axis = axis_or_button
        if axis == 1:
            X = pstn
            print 'X is at: %.4f' % X
            return X
            #GUI.window.progress_bar_x.setValue(X)
        elif axis == 2:
            Y = pstn
            #print 'Y is at: %.4f' % Y
        elif axis == 3:
            Throttle = pstn
            print 'Throttle is at: %.4f' % Throttle
        elif axis == 4:
            Z = pstn
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
        
        
    return X
    return Y
    return Throttle
    return Z
    


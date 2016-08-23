#!/usr/bin/env python

'''
 Joystick Handler module - Gives us current state of
 joystick to feed onto GUIllermo
'''

import pygame.joystick
import joystick_drawer
import GUI

joy = []

def ode_to_joy(window,j):
    'Here we pass we listen to the joystick movements and determine what they are'
    'j=argument that listen to the joystick'
    if j.type == pygame.JOYAXISMOTION:          #Here we listen for movements on the joysticks axes
        axis = "unknown"                        #If nothing comes through we call it <
        if (j.dict['axis'] == 0):               #movements on 0 = X axis movements
            axis = "X"
            
        if (j.dict['axis'] == 1):               #movements on 1 = Y axis movements
            axis = "Y"
        if (j.dict['axis'] == 2):               #movements on 2 = Throttle axis movements
            axis = "Throttle"
        if (j.dict['axis'] == 3):               #movements on 3 = z axis movements
            axis = "Z"

        if (axis != "unknown"):
            str = "Axis: %s; Val: %f" % (axis,j.dict['value'])  #If by any chance the code doesn't find some axis
                                                                #then we print the axis and its value to investigate which one it really is
            if (axis == "X"):
                pstn = j.dict['value']
                pstn = (pstn*50)+50
                GUI.paint_me_joy(window,1,pstn)
            if (axis == "Y"):
                pstn = j.dict['value']
                pstn = (pstn*50)+50
                GUI.paint_me_joy(window,2,pstn)
            if (axis == "Throttle"):
                pstn = j.dict['value']
                pstn = (pstn*-50)+50
                GUI.paint_me_joy(window,3,pstn)
            if (axis == "Z"):
                pstn = j.dict['value']
                pstn = (pstn*50)+50
                GUI.paint_me_joy(window,4,pstn)
     
    elif j.type == pygame.JOYBUTTONDOWN:
        if j.dict['button'] == 0:
            GUI.paint_me_joy(window,5,100)
        if j.dict['button'] == 1:
            GUI.paint_me_joy(window,6,100)
        if j.dict['button'] == 2:
            GUI.paint_me_joy(window,7,100)
        if j.dict['button'] == 3:
            GUI.paint_me_joy(window,8,100)
        if j.dict['button'] == 4:
            GUI.paint_me_joy(window,9,100)
        if j.dict['button'] == 5:
            GUI.paint_me_joy(window,10,100)
        if j.dict['button'] == 6:
            GUI.paint_me_joy(window,11,100)
        if j.dict['button'] == 7:
            GUI.paint_me_joy(window,12,100)
        if j.dict['button'] == 8:
            GUI.paint_me_joy(window,13,100)
        if j.dict['button'] == 9:
            GUI.paint_me_joy(window,14,100)
        if j.dict['button'] == 10:
            GUI.paint_me_joy(window,15,100)
        if j.dict['button'] == 11:
            GUI.paint_me_joy(window,16,100)

def ode_to_box(window,j):
    'Here we pass we listen to the Xbox controller movements and determine what they are'
    'j=argument that listen to the Xbox controller'
    if j.type == pygame.JOYAXISMOTION:          #Here we listen for movements on the joysticks axes
        axis = "unknown"                        #If nothing comes through we call it <
        if (j.dict['axis'] == 0):               #movements on 0 = X axis movements
            axis = "X"            
        if (j.dict['axis'] == 1):               #movements on 1 = Y axis movements
            axis = "Y"
        if (j.dict['axis'] == 2):               #movements on 2 = Throttle axis movements
            axis = "Throttle"
        if (j.dict['axis'] == 3):               #movements on 3 = z axis movements
            axis = "Z"

        if (axis != "unknown"):
            str = "Axis: %s; Val: %f" % (axis,j.dict['value'])  #If by any chance the code doesn't find some axis
                                                                #then we print the axis and its value to investigate which one it really is
            if (axis == "X"):
                pstn = j.dict['value']
                pstn = (pstn*50)+50
                GUI.paint_me_box(window,1,pstn)
            if (axis == "Y"):
                pstn = j.dict['value']
                pstn = (pstn*50)+50
                GUI.paint_me_box(window,2,pstn)
            if (axis == "Throttle"):
                pstn = j.dict['value']
                pstn = (pstn*-50)+50
                GUI.paint_me_box(window,3,pstn)
            if (axis == "Z"):
                pstn = j.dict['value']
                pstn = (pstn*50)+50
                GUI.paint_me_box(window,4,pstn)
     
    elif j.type == pygame.JOYBUTTONDOWN:
        if j.dict['button'] == 0:
            GUI.paint_me_box(window,5,100)
        if j.dict['button'] == 1:
            GUI.paint_me_box(window,6,100)
        if j.dict['button'] == 2:
            GUI.paint_me_box(window,7,100)
        if j.dict['button'] == 3:
            GUI.paint_me_box(window,8,100)
        if j.dict['button'] == 4:
            GUI.paint_me_box(window,9,100)
        if j.dict['button'] == 5:
            GUI.paint_me_box(window,10,100)
        if j.dict['button'] == 6:
            GUI.paint_me_box(window,11,100)
        if j.dict['button'] == 7:
            GUI.paint_me_box(window,12,100)
        if j.dict['button'] == 8:
            GUI.paint_me_box(window,13,100)
        if j.dict['button'] == 9:
            GUI.paint_me_box(window,14,100)
        if j.dict['button'] == 10:
            GUI.paint_me_box(window,15,100)
        if j.dict['button'] == 11:
            GUI.paint_me_box(window,16,100)        
	
	 
def joystick_listen(window,identifier):
    print 'Listening for Joystick movement...'
    
    while True:
        j = pygame.event.wait()
        if (j.type == pygame.JOYAXISMOTION or j.type == pygame.JOYBUTTONDOWN or j.type == pygame.JOYBUTTONUP or j.type == pygame.JOYHATMOTION):
            ode_to_joy(window,j)
def xbox_listen(window,identifier):
    print 'Listening for Xbox Controller movement...'
    while True:
        j = pygame.event.wait()
        if (j.type == pygame.JOYAXISMOTION or j.type == pygame.JOYBUTTONDOWN or j.type == pygame.JOYBUTTONUP or j.type == pygame.JOYHATMOTION):
            ode_to_box(window,j)
            
def main(window,status):
    if status == 0:                         #Control set to Joystick if status = 0
        pygame.joystick.init()
        pygame.display.init()
        if not pygame.joystick.get_count():
            print "\nPlease connect a joystick or Xbox 360 Controller run again.\n"
        print "\n%d joystick(s) detected." % pygame.joystick.get_count()

        for i in range(pygame.joystick.get_count()):
            ur_joystick = pygame.joystick.Joystick(i)
            ur_joystick.init()
            if ur_joystick.get_name() == 'Logitech Extreme 3D':
                joy.append(ur_joystick)
                joystick_listen(window,0)
            else:
                ur_joystick.quit()   
            
    elif status == 2:
        print 'blah'
        pygame.joystick.init()
        pygame.display.init()
        if not pygame.joystick.get_count():
            print "\nPlease connect a joystick or Xbox 360 Controller run again.\n"
        print "\n%d joystick(s) detected." % pygame.joystick.get_count()

        for i in range(pygame.joystick.get_count()):
            ur_joystick = pygame.joystick.Joystick(i)
            ur_joystick.init()
            if ur_joystick.get_name() == 'Controller (Xbox 360 Wireless Receiver for Windows)':
                joy.append(ur_joystick)
                xbox_listen(window,2)
                print 'ldfjvlkjdfvbdfbvljwhbflvhwbeofvjwfbdv'
            else:
                ur_joystick.quit()   
            

    elif status == 1:
        print 'not ON'
        pygame.joystick.quit()

if __name__ == "__main__":
    entrada = input("Enter 0 for ON| Enter 1 for OFF")
                     
    main(entrada)

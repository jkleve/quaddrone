
def keyPressEvent(window,eventQKeyEvent):
            key = eventQKeyEvent.key()
            
            if key == 87:
                    print 'FORWARD'
            elif key == 65:
                    print 'ROLL LEFT'
            elif key == 83:
                    print 'BACK'
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

//
// Created by jesse on 2/15/17.
//

extern "C" {
#include <avr/interrupt.h>
#include <avr/io.h> // TODO remove when done
#include <util/delay.h>
}

#include "ArduinoWrapper.h"
#include "QuadMgr.h"
#include "Timer1.h"
#include "Timer3.h"
#include "Timer4.h"
#include "Timer5.h"

Quad::QuadMgr::QuadMgr() :
    ledMgr( led::LedMgr::reference() ),
    commsMgr( comms::CommsMgr::reference() ),
    quadState( Quad::QuadState::reference() ),
    //interruptMgr( Quad::InterruptMgr::reference() ),
    eepromMgr( Eeprom::EepromMgr::reference() ),
    timer1_( timer::Timer1() ), // Allocated to MotorManager (front motors)
    timer3_( timer::Timer3() ), // Main processing timer
    timer4_( timer::Timer4() ), // Allocated to MotorManager (back motors)
    timer5_( timer::Timer5() ), // Allocated to ArduinoWrapper
    motors_( motor::MotorManager(timer1_, timer4_) ),
    ground_( ground::Ground::reference() ),
    mpu_( mpu::MpuMgr(ground_) )
{
    timer::setMillisTimer(timer5_);

    timer3_.setNormalMode();
    timer3_.setMs(50); // 20 Hz
    timer3_.start();

	_delay_ms(1000);
}

void Quad::QuadMgr::start()
{
    ledMgr.toggle(led::BLUE);

    ground_.sendString("Testing");
    ground_.test();
    ground_.sendString("Done Testing");

    _delay_ms(1000);
    ledMgr.toggle(led::BLUE);

    ground_.sendString("Initializing motors");
    motors_.initialize(motor::ALL_MOTORS);
}

void Quad::QuadMgr::loop() {
    bool tmp = true; // Damn clion highlights the never ending loop as an error unless I do this
    do {
        ground::Message message = ground_.getMessage();

        uint8_t power = message.data[0];
        motors_.setPower(motor::ALL_MOTORS, power);

        //interruptMgr.pollInterupts();

        // Processesing to be done at 20Hz.
        // TODO add error for if we are taking too long
        if( timer3_.check() )
        //if( quadState.getstate( MainProcessesing ) )
        {
            // need to move stuff here after debugging
            if( quadState.received() )
            {
                //uint8_t d = commsMgr.getChar();
                //commsMgr.putChar(d);
                quadState.unset( State::ReceivedMsg );
            }

            quadState.unset(MainProcessesing);
        }

        if( quadState.abort() )
        {
            // de-init
            break;
        }
    } while (tmp);
}

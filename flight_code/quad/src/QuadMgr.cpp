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
    mpu_( mpu::MpuMgr(ground_) ),
    userInput_( quad::UserInput() ),
    updateMotors_( false ),
    quaternion()
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
    uint8_t i = 0;
    uint8_t nSecondaryTasks = 2;
    double yawPitchRoll[3];

    bool tmp = true; // Damn clion highlights the never ending loop as an error unless I do this
    do {
        // Check important interrupts
        // Processing to be done at 20Hz.
        // TODO add error for if we are taking too long
        if( timer3_.check() )
        {
            timer3_.reset();

            // user input + PID processing
            ground_.sendString("Using input of");
            ground_.sendByte(userInput_.yaw);
            ground_.sendByte(userInput_.pitch);
            ground_.sendByte(userInput_.roll);
            ground_.sendByte(userInput_.throttle);

            // update motors
        }

        // Check less important interrupts
        if( i % nSecondaryTasks == 0 && ground_.received() ) {
            ground::Message message = ground_.getMessage();
            switch (message.msgType) {
                case ground::CONTROLS:
                    userInput_.yaw = message.data[ground::YAW];
                    userInput_.pitch = message.data[ground::PITCH];
                    userInput_.roll = message.data[ground::ROLL];
                    userInput_.throttle = message.data[ground::THROTTLE];
                    break;
                default:
                    break;
            }
        }

        if( i % nSecondaryTasks == 0 ) {
            // TODO what to do about return code on failures?
            mpu_.getQuaternion(quaternion);
            mpu_.getYawPitchRoll(yawPitchRoll);
            //uint8_t status = mpu_.getQuaternion(quaternion);
            //ground_.sendString("Status is:");
            //ground_.sendByte(status);
            //ground_.sendQuaternion(quaternion);
            ground_.sendYawPitchRoll(yawPitchRoll);
        }

        if( quadState.abort() )
        {
            // de-init
            break;
        }

        i++;
    } while (tmp);
}

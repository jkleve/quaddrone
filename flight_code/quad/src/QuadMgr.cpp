//
// Created by jesse on 2/15/17.
//

extern "C" {
#include <avr/interrupt.h>
#include <avr/io.h> // TODO remove when done
#include <util/delay.h>
}

#include "QuadMgr.h"
#include "Timer3.h"

Quad::QuadMgr::QuadMgr() :
    ledMgr( led::LedMgr::reference() ),
    commsMgr( comms::CommsMgr::reference() ),
    quadState( Quad::QuadState::reference() ),
    interruptMgr( Quad::InterruptMgr::reference() ),
    eepromMgr( Eeprom::EepromMgr::reference() ),
    twiMgr( twi::TwiMgr::reference() ),
    timer3_( timer::Timer3() ),
    ground_( ground::Ground::reference() )
	//i2cDriver( i2c::AVRI2CDriver() )
{
	_delay_ms(1000);
	//i2cDriver.begin();
    sei();
}

void Quad::QuadMgr::start()
{

    ledMgr.toggle(led::BLUE);

    ground_.sendString("Testing");
    ground_.test();
    ground_.sendString("Done Testing");

    _delay_ms(1000);
    ledMgr.toggle(led::BLUE);

    timer3_.setNormalMode();
    timer3_.disableOutputCompare();
    timer3_.setPrescaler(timer::Prescaler::PRESCALE256); // TODO
    timer3_.setMs(1000);
    timer3_.start();

    while (true) {
        if (timer3_.check()) {
            ledMgr.toggle(led::YELLOW);
            ground_.sendString("Interrupt ...");
            timer3_.reset();
        }
        //ground_.sendRegister(reg::TIMER3_COUNTER, TCNT3);
    }

    //twiMgr.writeByte(0x68, 0x6B, 1);

    ledMgr.toggle(led::RED);

    // loop
    //loop();
}

//void Quad::QuadMgr::loop() {
//    do {
//        interruptMgr.pollInterupts();
//
//        // Processesing to be done at 20Hz.
//        // TODO add error for if we are taking too long
//        if( quadState.getstate( MainProcessesing ) )
//        {
//            // need to move stuff here after debugging
//            if( quadState.received() )
//            {
//                uint8_t d = commsMgr.getChar();
//                commsMgr.putChar(d);
//                quadState.unset( State::ReceivedMsg );
//            }
//
//            quadState.unset(MainProcessesing);
//        }
//
//        if( quadState.getstate( OneHzTimer ) )
//        {
//            ledMgr.toggle( led::RED );
//            quadState.unset(OneHzTimer);
//        }
//
//        if( quadState.abort() )
//        {
//            // de-init
//            break;
//        }
//    } while (true);
//}

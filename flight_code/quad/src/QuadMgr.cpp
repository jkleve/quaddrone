//
// Created by jesse on 2/15/17.
//

extern "C" {
#include <avr/interrupt.h>
#include <avr/io.h> // TODO remove when done
#include <util/delay.h>
}

#include "QuadMgr.h"
#include "I2C.h"
#include "Timer3.h"
#include "Timer5.h"

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

    timer::Timer5 timer5;

    ground_.sendString("F_CPU Kilo Hz is");
    ground_.sendWord(timer::Timer16::F_CPU_KILO_HZ);
    timer5.setNormalMode();
    timer5.disableOutputCompare();
    timer5.setPrescaler(timer::PRESCALE256);
    //timer5.millis();

    //timer5.millis(true);
    //_delay_ms(1000);
    //timer5.millis();
    while (true) {
        if (timer5.millis() > 1000.0) {
            ledMgr.toggle(led::BLUE);
            timer5.millis(true);
            ground_.sendString("heartbeat");
        }
      //ground_.sendString(".");
    }

    return;
//    I2C i2c(ground_, timer5);
//    i2c.scan();

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

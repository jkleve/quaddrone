//
// Created by jesse on 2/15/17.
//

extern "C" {
#include <avr/interrupt.h>
#include <avr/io.h> // TODO remove when done
#include <util/delay.h>
}

#include "QuadMgr.h"
#include "I2Cdev.h"
#include "Timer3.h"
#include "Timer5.h"

Quad::QuadMgr::QuadMgr() :
    ledMgr( led::LedMgr::reference() ),
    commsMgr( comms::CommsMgr::reference() ),
    quadState( Quad::QuadState::reference() ),
    interruptMgr( Quad::InterruptMgr::reference() ),
    eepromMgr( Eeprom::EepromMgr::reference() ),
    timer3_( timer::Timer3() ),
    timer5_( timer::Timer5() ),
    ground_( ground::Ground::reference() )
{
    timer::setMillisTimer(timer5_);
	_delay_ms(1000);
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

    timer5.setNormalMode();
    timer5.disableOutputCompare();
    timer5.setPrescaler(timer::PRESCALE256);

    //I2C i2c(ground_, timer5);
    //uint8_t response = i2c.read(0x68, 0x75, 1);
    uint8_t data[10];
    int8_t response = I2Cdev::readByte(0x68, 0x75, data);
    ground_.sendString("Reading 0x75 from 0x68. Response:");
    ground_.sendByte(response);

   if (response > 0) {
        for (int8_t i = 0; i < response; i++) {
            ground_.sendString("Received");
            ground_.sendByte(data[i]);
        }
    }
    //i2c.scan();

    //twiMgr.writeByte(0x68, 0x6B, 1);

    ledMgr.toggle(led::RED);

    // loop
    loop();
}

void Quad::QuadMgr::loop() {
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
}

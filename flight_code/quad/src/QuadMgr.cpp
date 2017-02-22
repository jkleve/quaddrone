//
// Created by jesse on 2/15/17.
//

extern "C" {
#include <avr/io.h> // TODO remove when done
}

#include "QuadMgr.h"

Quad::QuadMgr::QuadMgr() :
    ledMgr( LED::LedMgr::reference() ),
    commsMgr( Comms::CommsMgr::reference() ),
    quadState( Quad::QuadState::reference() ),
    interruptMgr( Quad::InterruptMgr::reference() ),
    eepromMgr( Eeprom::EepromMgr::reference() )
{

}

void Quad::QuadMgr::start()
{
    // init

    // loop
    loop();
}

void Quad::QuadMgr::loop() {
    do {
        interruptMgr.pollInterupts();

        // Processesing to be done at 20Hz.
        // TODO add error for if we are taking too long
        if( quadState.getstate( MainProcessesing ) )
        {
            // need to move stuff here after debugging
            if( quadState.received() )
            {
                uint8_t d = commsMgr.getChar();
                commsMgr.putChar(d);
                quadState.unset( State::ReceivedMsg );
            }

            quadState.unset(MainProcessesing);
        }

        if( quadState.getstate( OneHzTimer ) )
        {
            ledMgr.toggle( LED::RED );
            quadState.unset(OneHzTimer);
        }

        if( quadState.abort() )
        {
            // de-init
            break;
        }
    } while (true);
}

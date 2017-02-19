//
// Created by jesse on 2/15/17.
//

extern "C" {
#include <util/delay.h>
}

#include "QuadMgr.h"

Quad::QuadMgr::QuadMgr() :
    ledMgr( LED::LedMgr::reference() ),
    commsMgr( Comms::CommsMgr::reference() ),
    quadState( Quad::QuadState::reference() ),
    interruptMgr( Quad::InterruptMgr::reference() )
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
        if( quadState.getstate( MainProcessesing ) )
        {
            // main processesing
            ledMgr.toggle( LED::RED );

            quadState.unset(MainProcessesing);
        }

        // move this to 10 - 20 Hz processing
        if( quadState.received() )
        {
            // TODO add a buffer and receive a "frame" or "packet"
            //uint8_t data = commsMgr.getChar();
        }

        if( quadState.abort() )
        {
            // de-init
            break;
        }
    } while (true);
}

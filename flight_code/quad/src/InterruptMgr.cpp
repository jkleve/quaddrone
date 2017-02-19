//
// Created by jesse on 2/15/17.
//

#include "InterruptMgr.h"

extern "C" {
#include <avr/io.h>
}

Quad::InterruptMgr::InterruptMgr() :
    quadState( QuadState::reference() ),
    mainTimer( TCNT0 ),
    mainTimerInterruptReg( TIFR0 ),
    MAIN_TIMER_OVERFLOW( TOV0 ),
    MAIN_TIMER_THRESHOLD( 134 ) // overflows at 255. For 20Hz we need 390 ticks.
{
    initMainTimer();
}

void Quad::InterruptMgr::pollInterupts( void ) {
    if( (UCSR0A & (1<<UDRE0)) )
    {
        //can_tx = true; // tx buffer empty TODO get rid of this
        quadState.set( State::CanTx );
    }

    if( (UCSR0A & (1<<RXC0)) )
    {
        //rx = true; // rx buffer has data TODO get rid of this
        quadState.set( State::ReceivedMsg );
    }

    // Main processing should happen at 20Hz. This is 391 ticks when
    // using clk/1024. Since we are using a 8 bit timer we need 1
    // full count of 255 to get the overflow and 135 more tickets.
    // If we miss one cycle we will drop to 12Hz.
    if( mainTimer > MAIN_TIMER_THRESHOLD && (mainTimerInterruptReg & (1 << MAIN_TIMER_OVERFLOW)) )
    {
        quadState.set( State::MainProcessesing );

        // clear overflow flag
        mainTimerInterruptReg &= ~(1 << MAIN_TIMER_OVERFLOW); // TODO move this type of logic into Register class making
                                                              //      mainTimerInterruptReg a Register class
        // reset timer
        mainTimer = 0;
    }
}

Quad::InterruptMgr &Quad::InterruptMgr::reference( void ) {
    static Quad::InterruptMgr ref;
    return ref;
}

void Quad::InterruptMgr::initMainTimer( void )
{
    TCCR0A |= (0 << WGM01)  | (0 << WGM00)  | // normal mode 0
              (0 << COM0A1) | (0 << COM0A0) | // disable compare on match A
              (0 << COM0B1) | (0 << COM0B0);  // disable compare on match B
    TCCR0B =  (1 << CS02) | (0 << CS01) | (1 << CS00) | // clock select 5 (clk / 1024). clock select starts time
              (0 << WGM02); // normal mode 0
}

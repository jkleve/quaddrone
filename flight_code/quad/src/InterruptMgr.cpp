//
// Created by jesse on 2/15/17.
//

#include "InterruptMgr.h"

extern "C" {
#include <avr/io.h>
}

Quad::InterruptMgr::InterruptMgr() :
    quadState( QuadState::reference() ),
    timer0( Timer0::reference() ),
    timer1( Timer1::reference() ),
    ledMgr( LED::LedMgr::reference() ),
    eepromMgr( Eeprom::EepromMgr::reference() )
{
    // timer 1 (1 Hz)
    timer1.set_ms(1000);
    timer1.start();
    initMainTimer();
}

void Quad::InterruptMgr::pollInterupts( void ) {
    //if( (UCSR0A & (1 << UDRE0)) )
    //{
    //    quadState.set( State::CanTx );
    //}
    //else
    //{
    //    quadState.unset( State::CanTx );
    //}

    if( (UCSR0A & (1 << RXC0)) ) // receive complete flag in UART0 controller & status register A
    {
        quadState.set( State::ReceivedMsg );
    }
    //else
    //{
    //    quadState.unset( State::ReceivedMsg );
    //}

    // check 1 Hz timer
    if( timer1.check() )
    {
        quadState.set( State::OneHzTimer );
        timer1.reset();
    }

    if( timer0.check() )
    {
        quadState.set( State::MainProcessesing );

        // reset timer
        timer0.reset();
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

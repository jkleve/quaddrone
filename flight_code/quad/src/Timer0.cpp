//
// Created by jesse on 2/21/17.
//

extern "C" {
#include <avr/io.h>
}

#include "Timer0.h"

// Main processing should happen at 20Hz. This is 391 ticks when
// using clk/1024. Since we are using a 8 bit timer we need 1
// full count of 255 to get the overflow and 135 more tickets.
// If we miss one cycle we will drop to 12Hz.

// TCNT0: Timer 0 timer/counter.
// TIFR0: Timer 0 Interrupt Flag Register
//  - TOV0: Timer 0 Overflow flag

Timer0::Timer0()
{
    TCCR0A |= (0 << WGM01)  | (0 << WGM00)  | // normal mode 0
              (0 << COM0A1) | (0 << COM0A0) | // disable compare on match A
              (0 << COM0B1) | (0 << COM0B0);  // disable compare on match B
    TCCR0B =  (1 << CS02) | (0 << CS01) | (1 << CS00) | // clock select 5 (clk / 1024). clock select starts time
              (0 << WGM02); // normal mode 0

    top = 134;
}

Timer0 &Timer0::reference( void ) {
    static Timer0 ref;
    return ref;
}

bool Timer0::check()
{
    // true if we passed top and have overflowed
    return ( (TCNT0 > top) && (TIFR0 & (1 << TOV0)) );
}

void Timer0::reset()
{
    // clear overflow flag
    TIFR0 &= ~(1 << TOV0);
}

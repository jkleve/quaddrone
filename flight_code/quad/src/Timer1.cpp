//
// Created by jesse on 2/20/17.
//

extern "C" {
#include <avr/io.h>
}

#include <stdint.h>

#include "QuadParams.h"
#include "Timer1.h"


Timer1::Timer1() :
    running( false )
{
    TCCR1A = (0 << WGM11) | (0 << WGM10); // no PWM
    TCCR1B = (0 << WGM13) | (0 << WGM12); // normal mode
    TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10); // clk / 256. this starts counting
}

Timer1 &Timer1::reference( void ) {
    static Timer1 ref;
    return ref;
}

void Timer1::set_ms(uint16_t ms)
{
    uint16_t ticks = ms * (F_CPU / 256) / 1000; // 256 is the clk divider
    top = ticks;
}

void Timer1::start()
{
    reset();
    running = true;
}

bool Timer1::check()
{
    if( running )
        return ( (TCNT1 > top) || ((1 << TOV1) && TIFR1) ); // true if we passed top or have overflowed
    return false;
}

void Timer1::reset()
{
    TIFR1 &= ~(1 << TOV1); // make sure overflow flag is off
    TCNT1 = 0; // reset timer to 0
}
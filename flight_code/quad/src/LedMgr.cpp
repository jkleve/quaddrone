//
// Created by jesse on 2/17/17.
//

extern "C" {
#include <avr/io.h>
}
#include "LedMgr.h"

led::LedMgr::LedMgr() {
    // BLUE:   0x08 PA3
    // YELLOW: 0x10 PA4
    // RED:    0x20 PA5
    DDRA = (1 << DDA3) | (1 << DDA4) | (1 << DDA5); // set as outputs
    PORTA = 0xFF; // turn all pins off
}

led::LedMgr &led::LedMgr::reference( void ) {
    static LedMgr ref;
    return ref;
}

void led::LedMgr::toggle( LED light )
{
    switch( light )
    {
        case BLUE:
            PORTA ^= 0x08;
            break;
        case YELLOW:
            PORTA ^= 0x10;
            break;
        case RED:
            PORTA ^= 0x20;
            break;
        default:
            break;
    }
}

void led::LedMgr::on( LED light )
{
    switch( light )
    {
        case BLUE:
            PORTA |= 0x08;
            break;
        case YELLOW:
            PORTA |= 0x10;
            break;
        case RED:
            PORTA |= 0x20;
            break;
        default:
            break;
    }
}

void led::LedMgr::off( LED light )
{
    switch( light )
    {
        case BLUE:
            PORTA &= ~0x08;
            break;
        case YELLOW:
            PORTA &= ~0x10;
            break;
        case RED:
            PORTA &= ~0x20;
            break;
        default:
            break;
    }
}

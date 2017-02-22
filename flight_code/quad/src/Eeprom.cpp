//
// Created by jesse on 2/13/17.
//

#include "Eeprom.h"

extern "C" {
#include <avr/io.h>
}

Eeprom::EepromMgr::EepromMgr() :
    writeAddress( 0x00 ),
    writeData( 0x00 )
{

}

Eeprom::EepromMgr &Eeprom::EepromMgr::reference() {
    static Eeprom::EepromMgr ref;
    return ref;
}

void Eeprom::EepromMgr::write(uint8_t d)
{
    while( EECR & (1 << EEPE) )
        ;
    EEAR = writeAddress++; // increment address
    EEDR = d; // set write buffer
    EECR |= (1 << EEMPE);
    EECR |= (1 << EEPE); // write
}



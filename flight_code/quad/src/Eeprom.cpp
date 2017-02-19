//
// Created by jesse on 2/13/17.
//

#include "Eeprom.h"

extern "C" {
#include <avr/io.h>
}

Eeprom::EepromMgr::EepromMgr() {
    EEAR = 0x00;
}

Eeprom::EepromMgr::~EepromMgr() {

}

void Eeprom::EepromMgr::write(char *d) {
    while( EECR & (1 << EEPE) )
        ;
    EEDR = (uint8_t) *d; // set write buffer
    EECR |= (1 << EEMPE);
    EECR |= (1 << EEPE); // write
    EEAR += 0x01; // increment address
}



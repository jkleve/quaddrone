//
// Created by jesse on 6/30/17.
//

#ifndef REGISTERS_H
#define REGISTERS_H

namespace registers {
    enum Address {
        // twi
        REG_TWI_STATUS = 0xB9,
        TWI_CONTROL = 0xBC,
        TWI_DATA = 0xBB
    };
}

#endif // REGISTERS_H

//
// Created by jesse on 6/30/17.
//

#ifndef GROUND_H
#define GROUND_H

#include "CommsMgr.h"
#include "Registers.h"

namespace comms {
    class CommsMgr;
}

namespace ground {

    static const uint8_t HEADER_LEN = 1;
    static const uint8_t TWI_MSG_LEN = HEADER_LEN + 1;
    static const uint8_t REGISTER_MSG_LEN = HEADER_LEN + 2;

    enum MsgType {
        STRING = 0xff,
        TWI_MESSAGE = 0xfe,
        REGISTER = 0xfd
    };

    struct Message {
        uint8_t msgType;
        uint8_t* data;
        uint8_t nData;
    };

    class Ground {
    public:
        static Ground& reference();
        void sendRegister(registers::Address register, uint8_t value);
        void sendString(const char* string);
        void sendTwiMessage(uint8_t twi_message);
        void test();
    private:
        Ground();

        comms::CommsMgr& comms_;
    };
}

#endif // GROUND_H

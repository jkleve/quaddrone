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
    static const uint8_t REGISTER_MSG_LEN = HEADER_LEN + 4; // lowRegByte, highRegByte, lowByte, highByte
    static const uint8_t WORD_MSG_LEN = HEADER_LEN + 2;

    enum MsgType {
        STRING      = 0xff,
        TWI_MESSAGE = 0xfe,
        REGISTER    = 0xfd,
        DATA        = 0xfc,
        WORD        = 0xfb
    };

    struct Message {
        uint8_t msgType;
        uint8_t* data;
        uint8_t nData;
    };

    class Ground {
    public:
        static const uint8_t MAX_BUFFER_SIZE = 64;

        static Ground& reference();
        void sendRegister( reg::Address register,
                           uint8_t lowByte,
                           uint8_t highByte = 0);
        void sendString(const char* string);
        void sendTwiMessage(uint8_t twi_message);
        void sendData(uint8_t* data, uint8_t nData);
        void sendWord(uint16_t word);
        void test();
    private:
        Ground();

        uint8_t buffer_[MAX_BUFFER_SIZE];
        comms::CommsMgr& comms_;
    };
}

#endif // GROUND_H

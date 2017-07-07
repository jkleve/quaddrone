//
// Created by jesse on 2/14/17.
//

#ifndef COMMS_COMMSMGR_H
#define COMMS_COMMSMGR_H

#include <stdint.h>

namespace ground {
    struct Message;
}

namespace comms {

    #define USART_BAUD	38400UL		// Define Baud rate

    static const uint8_t END_PACKET = 0x00;

    class CommsMgr {
    public:
        static CommsMgr& reference();
        void sendMessage(const uint8_t* data, uint8_t nData);
    private:
        CommsMgr();
        uint8_t getChar(void);
        void putChar(uint8_t byte);
        uint8_t getChecksum(const uint8_t * data, uint8_t nData);
    };
}

#endif // COMMS_COMMSMGR_H

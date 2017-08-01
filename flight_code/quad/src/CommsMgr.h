//
// Created by jesse on 2/14/17.
//

#ifndef COMMS_COMMSMGR_H
#define COMMS_COMMSMGR_H

#include <stdint.h>

namespace comms {

    #define USART_BAUD	38400UL		// Define Baud rate

    class CommsMgr {

    public:
        static CommsMgr& reference();
        void sendMessage(const uint8_t* data, uint8_t nData);
        uint8_t getMessage(uint8_t* data, uint8_t timeout=10);
        bool received();

    private:
        static const uint8_t UPLINK_HEADER = 0x42;
        static const uint8_t COMMS_BUFFER_SIZE = 8;

        uint8_t buffer_[COMMS_BUFFER_SIZE];

        CommsMgr();
        uint8_t getChar(void);
        void putChar(uint8_t byte);
        uint8_t getChecksum(const uint8_t * data, uint8_t nData);
    };
}

#endif // COMMS_COMMSMGR_H

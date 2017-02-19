//
// Created by jesse on 2/14/17.
//

#ifndef COMMS_COMMSMGR_H
#define COMMS_COMMSMGR_H

#include <stdint.h>

namespace Comms {

    #define USART_BAUD	38400UL		// Define Baud rate
    uint8_t const FrameHeader = 0x02;


    class CommsMgr {
        public:
            static CommsMgr& reference();
            void putChar(uint8_t byte);
            uint8_t getChar(void);
        private:
            CommsMgr();
    };
}


#endif //COMMS_COMMSMGR_H

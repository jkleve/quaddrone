//
// Created by jesse on 2/14/17.
//

#ifndef COMMS_COMMSMGR_H
#define COMMS_COMMSMGR_H

#include <stdint.h>

namespace Comms {

    // Modes
    //static const START

    #define USART_BAUD	38400UL		// Define Baud rate
    uint8_t const FrameHeader = 0x02;

    enum MsgType {
        STRING,
        TWI_MESSAGE
    };

    struct Frame {
        uint8_t msg;
        uint8_t throttle;
        uint8_t roll;
        uint8_t pitch;
        uint8_t yaw;
    };

    class CommsMgr {
        public:
            static CommsMgr& reference();
            void putChar(uint8_t byte);
            uint8_t getChar(void);
            Frame getFrame(void);
            void sendString(const char* string);
            void sendTwiMsg(const char msg);
            //void sendMsg(const char* string, MsgType msg_type);
        private:
            CommsMgr();
    };
}


#endif //COMMS_COMMSMGR_H

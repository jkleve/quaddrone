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

    enum PktType {
        STRING = 0xff,
        TWI_MESSAGE = 0xfe
    };

    struct Packet {
        PktType pktType;
        uint8_t* data;
        uint8_t nData;
        uint8_t checksum;
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
            void sendPacket(const Packet packet);
            //void sendMsg(const char* string, PktType msg_type);
        private:
            CommsMgr();
            uint8_t getChecksum(const uint8_t * data, uint8_t nData);
    };
}


#endif //COMMS_COMMSMGR_H

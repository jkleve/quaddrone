//
// Created by jesse on 6/30/17.
//

#ifndef GROUND_H
#define GROUND_H

#include "CommsMgr.h"
#include "Registers.h"
#include "UserInput.h"
#include "helper_3dmath.h"

namespace comms {
    class CommsMgr;
}

namespace ground {

    static const uint8_t HEADER_LEN = 1;
    static const uint8_t TWI_MSG_LEN = HEADER_LEN + 1;
    static const uint8_t REGISTER_MSG_LEN = HEADER_LEN + 4; // lowRegByte, highRegByte, lowByte, highByte
    static const uint8_t WORD_MSG_LEN = HEADER_LEN + 2;
    static const uint8_t BYTE_MSG_LEN = HEADER_LEN + 1;
    static const uint8_t SIZE32_MSG_LEN = HEADER_LEN + 4;

    enum MsgType {
        STRING      = 0xff,
        TWI_MESSAGE = 0xfe,
        REGISTER    = 0xfd,
        DATA        = 0xfc,
        WORD        = 0xfb,
        BYTE        = 0xfa,
        QUATERNION  = 0xf9,
        SIZE_32     = 0xf8,
        YAWPITCHROLL = 0xf7,
        CONTROLS    = 0xcf
    };

    enum Control {
        YAW = 0,
        PITCH = 1,
        ROLL = 2,
        THROTTLE = 3
    };


    struct Message {
        uint8_t msgType;
        uint8_t* data;
        uint8_t nData;
    };

    class Ground {
    public:
        static const uint8_t GROUND_MAX_BUFFER_SIZE = 64;

        static Ground& reference();
        void sendRegister( reg::Address register,
                           uint8_t lowByte,
                           uint8_t highByte = 0);
        void sendString(const char* string);
        void sendTwiMessage(uint8_t twi_message);
        void sendData(uint8_t* data, uint8_t nData);
        void sendWord(uint16_t word);
        void send32(uint32_t data);
        void sendByte(uint8_t byte);
        void sendQuaternion(const char* quat);
        void sendQuaternion(Quaternion&);
        void sendQuaternion(Quaternion*);
        void sendYawPitchRoll(double[]);
        bool received();
        Message getMessage();
        void test();
    private:
        Ground();

        uint8_t buffer_[GROUND_MAX_BUFFER_SIZE];
        comms::CommsMgr& comms_;
    };
}

#endif // GROUND_H

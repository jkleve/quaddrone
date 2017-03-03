//
// Created by jesse on 2/22/17.
//

#ifndef AVR_CPP_EXAMPLE_TWI_H
#define AVR_CPP_EXAMPLE_TWI_H

#include <stdint.h>

#include "CommsMgr.h"
#include "Eeprom.h"

const uint32_t I2C_BAUD = 400000; // fast mode (400 kHz)

namespace twi {
    class TwiMgr {
        public:
            static TwiMgr& reference();
            bool writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
            bool writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data);
            void request_read(uint8_t addr, uint8_t reg);
        private:
            TwiMgr();
            Comms::CommsMgr& comms;
            Eeprom::EepromMgr& eeprom;
            int8_t readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint16_t timeout);
            bool writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data);
            bool writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data);
            int8_t readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data, uint16_t timeout);
            void print_status();
            bool idle();
            void sendStart();
    };
}

#endif //AVR_CPP_EXAMPLE_TWI_H

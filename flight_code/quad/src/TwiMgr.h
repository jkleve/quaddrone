//
// Created by jesse on 2/22/17.
//

#ifndef TWIMGR_H
# define TWIMGR_H

# include <stdint.h>

# include "CommsMgr.h"
# include "Eeprom.h"

const uint32_t I2C_BAUD = 400000; // fast mode (400 kHz)

namespace twi {

    // Common
    static const uint8_t START_TRANSMITTED          = 0x08;
    static const uint8_t REPEATED_START_TRANSMITTED = 0x10;
    static const uint8_t ARBITRATION_LOST           = 0x38;

    // Master Transmit mode
    static const uint8_t SLA_W_SENT_ACK_RECEIVED    = 0x18;
    static const uint8_t SLA_W_SENT_NOTACK_RECEIVED = 0x20;
    static const uint8_t TX_MODE_DATA_ACK           = 0x28;
    static const uint8_t TX_MODE_DATA_NOTACK        = 0x30;

    // Master Receiver mode
    static const uint8_t SLA_R_SENT_ACK_RECEIVED    = 0x40;
    static const uint8_t SLA_R_SENT_NOTACK_RECEIVED = 0x48;
    static const uint8_t RX_MODE_DATA_ACK           = 0x50;
    static const uint8_t RX_MODE_DATA_NOTACK        = 0x58;


    class TwiMgr {
        public:
            static TwiMgr& reference();
            bool writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
            bool writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data);
            void test_read(uint8_t addr);
            void request_read(uint8_t addr, uint8_t reg);
            uint8_t i2c_start(uint8_t);
            void i2c_start_wait(unsigned char address);
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
            void sla_r(uint8_t addr);
            void repeatedStart();
    };
}

#endif // TWIMGR_H

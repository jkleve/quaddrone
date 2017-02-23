//
// Created by jesse on 2/22/17.
//

#ifndef AVR_CPP_EXAMPLE_IMUMGR_H
#define AVR_CPP_EXAMPLE_IMUMGR_H

#include <stdint.h>

#include "TwiMgr.h"

// MPU 6050
namespace MPU {
    const uint8_t DEFAULT_ADDR = 0x68;
    const uint8_t GYRO_CONFIG_REG = 0x1B; // set to 1000 FS_SEL = 1 (bits 3 & 4)
    const uint8_t ACCEL_CONFIG_REG = 0x1C; // set to 8 AFS_SEL = 2 (bits 3 & 4)
    const uint8_t FIFO_REG = 0x23; // not sure if FIFO buffer is needed
    const uint8_t PWR_MGMT_REG = 0x6B; //
}

namespace IMU {
    class ImuMgr {
        public:
            static ImuMgr& reference();
        private:
            ImuMgr();
            Twi::TwiMgr& twi;
            const uint8_t devAddr;
            void setClockSource(uint8_t);
            void setFullScaleGyroRange(uint8_t);
            void setFullScaleAccelRange(uint8_t);
            void setSleepEnabled(bool);
    };
}


#endif //AVR_CPP_EXAMPLE_IMUMGR_H

//
// Created by jesse on 2/15/17.
//

#ifndef EEPROM_CMAKE_TEST_INTERRUPTMGR_H
#define EEPROM_CMAKE_TEST_INTERRUPTMGR_H

#include <stdint.h>
#include "QuadState.h"

namespace Quad {
    class InterruptMgr {
        public:
            static InterruptMgr& reference();
            void pollInterupts(void); // poll interupts
        private:
            InterruptMgr();
            void initMainTimer();
            QuadState& quadState;
            volatile uint8_t mainTimer;
            volatile uint8_t mainTimerInterruptReg;
            const uint8_t MAIN_TIMER_OVERFLOW;
            const uint8_t MAIN_TIMER_THRESHOLD;
    };
}


#endif //EEPROM_CMAKE_TEST_INTERRUPTMGR_H

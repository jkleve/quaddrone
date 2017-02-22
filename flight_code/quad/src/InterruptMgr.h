//
// Created by jesse on 2/15/17.
//

#ifndef EEPROM_CMAKE_TEST_INTERRUPTMGR_H
#define EEPROM_CMAKE_TEST_INTERRUPTMGR_H

#include <stdint.h>
#include "QuadState.h"
#include "Timer0.h"
#include "Timer1.h"
#include "LedMgr.h"
#include "Eeprom.h"

namespace Quad {
    class InterruptMgr {
        public:
            static InterruptMgr& reference();
            void pollInterupts(void); // poll interupts
        private:
            InterruptMgr();
            void initMainTimer();
            QuadState& quadState;
            Timer0& timer0;
            Timer1& timer1;
            LED::LedMgr& ledMgr;
            Eeprom::EepromMgr& eepromMgr;
    };
}


#endif //EEPROM_CMAKE_TEST_INTERRUPTMGR_H

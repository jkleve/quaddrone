//
// Created by jesse on 2/15/17.
//

#ifndef EEPROM_CMAKE_TEST_QUAD_H
#define EEPROM_CMAKE_TEST_QUAD_H

#include "QuadState.h"
#include "InterruptMgr.h"
#include "Eeprom.h"
#include "CommsMgr.h"
#include "LedMgr.h"
#include "TwiMgr.h"

namespace Quad {
    //class QuadState;
    //class InterruptMgr;

    class QuadMgr {
        public:
            QuadMgr();
            void start();
        private:
            LED::LedMgr& ledMgr;
            Comms::CommsMgr& commsMgr;
            QuadState& quadState;
            InterruptMgr& interruptMgr;
            Eeprom::EepromMgr& eepromMgr;
            twi::TwiMgr& twiMgr;

            void loop();
    };
}


#endif //EEPROM_CMAKE_TEST_QUAD_H

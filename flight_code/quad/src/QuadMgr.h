//
// Created by jesse on 2/15/17.
//

#ifndef EEPROM_CMAKE_TEST_QUAD_H
#define EEPROM_CMAKE_TEST_QUAD_H

#include "CommsMgr.h"
#include "QuadState.h"
#include "Eeprom.h"
#include "InterruptMgr.h"
#include "Ground.h"
//#include "I2CDriver.h"
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
        comms::CommsMgr& commsMgr;
        QuadState& quadState;
        InterruptMgr& interruptMgr;
        Eeprom::EepromMgr& eepromMgr;
        twi::TwiMgr& twiMgr;
        //i2c::AVRI2CDriver i2cDriver;

        void loop();

        ground::Ground& ground_;
    };
}


#endif //EEPROM_CMAKE_TEST_QUAD_H

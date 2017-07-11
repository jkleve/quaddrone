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
#include "Timer.h"
#include "TwiMgr.h"

namespace Quad {
    //class QuadState;
    //class InterruptMgr;

    class QuadMgr {
    public:
        QuadMgr();
        void start();
    private:
        led::LedMgr& ledMgr;
        comms::CommsMgr& commsMgr; // TODO make comms interface with usart class
        QuadState& quadState;
        InterruptMgr& interruptMgr;
        Eeprom::EepromMgr& eepromMgr;
        twi::TwiMgr& twiMgr;
        //i2c::AVRI2CDriver i2cDriver;

        void loop();

        // TODO timer0
        // TODO timer1
        // TODO timer2
        timer::Timer16 timer3_;
        // TODO timer4
        // TODO timer5
        // TODO motor front_star
        // TODO motor front_port
        // TODO motor back_start
        // TODO motor back_port
        ground::Ground& ground_;
    };
}


#endif //EEPROM_CMAKE_TEST_QUAD_H

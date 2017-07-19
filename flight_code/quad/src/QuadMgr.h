//
// Created by jesse on 2/15/17.
//

#ifndef EEPROM_CMAKE_TEST_QUAD_H
#define EEPROM_CMAKE_TEST_QUAD_H

#include "CommsMgr.h"
#include "Eeprom.h"
//#include "InterruptMgr.h"
#include "Ground.h"
#include "LedMgr.h"
#include "Motor.h"
#include "MPU6050.h"
#include "QuadState.h"
#include "Timer.h"

namespace Quad {

    class QuadMgr {
    public:
        QuadMgr();
        void start();
    private:
        led::LedMgr& ledMgr;
        comms::CommsMgr& commsMgr; // TODO make comms interface with usart class
        QuadState& quadState;
        //InterruptMgr& interruptMgr;
        Eeprom::EepromMgr& eepromMgr;

        void loop();

        // TODO timer0
        timer::Timer16 timer1_;
        // TODO timer2
        timer::Timer16 timer3_;
        // TODO timer4
        timer::Timer16 timer5_;
        // TODO motor front_star
        motor::Motor motor1_;
        // TODO motor front_port
        // TODO motor back_start
        // TODO motor back_port
        ground::Ground& ground_;

        MPU6050 mpu;
    };
}


#endif //EEPROM_CMAKE_TEST_QUAD_H

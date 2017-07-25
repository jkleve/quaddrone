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
#include "MotorManager.h"
#include "QuadState.h"
#include "Timer.h"
#include "Mpu.h"

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
        timer::Timer16 timer4_;
        timer::Timer16 timer5_;
        motor::MotorManager motors_;
        // TODO motor front_star
        //motor::Motor motor1_;
        // TODO motor front_port
        // TODO motor back_start
        // TODO motor back_port
        ground::Ground& ground_;

        mpu::MpuMgr mpu_;
    };
}


#endif //EEPROM_CMAKE_TEST_QUAD_H

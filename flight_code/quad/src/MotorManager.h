//
// Created by jesse on 7/19/17.
//

#pragma once

#include "Motor.h"
#include "Timer.h"

namespace motor {

    enum MotorSelect {
        MOTOR1,
        MOTOR2,
        MOTOR3,
        MOTOR4,
        ALL_MOTORS
    };

    // This class allows up to 6 motors assuming all output compare channels are
    // open on both timers
    class MotorManager {
    public:
        MotorManager(timer::Timer16&, timer::Timer16&);
        void initialize(MotorSelect);
        void setPower(MotorSelect motor, uint8_t power);
    private:
        timer::Timer16& timer1_; // Front motors
        timer::Timer16& timer2_; // Back motors
        Motor fl_motor_; // front left  (motor 1)
        Motor fr_motor_; // front right (motor 2)
        Motor bl_motor_; // back left   (motor 3)
        Motor br_motor_; // back right  (motor 4)
    };
}


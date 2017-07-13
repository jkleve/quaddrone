//
// Created by jesse on 7/10/17.
//

#ifndef MOTOR_H
#define MOTOR_H

#include "Timer.h"

class Motor {
public:
    Motor(timer::Timer16& timer);
    void setPower(uint8_t);

private:
    timer::Timer16 timer_;
    uint8_t power_; // TODO can this be a new type with specific range?
};


#endif // MOTOR_H

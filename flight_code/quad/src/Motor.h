//
// Created by jesse on 7/16/17.
//

#ifndef AVR_CPP_EXAMPLE_MOTOR_H
#define AVR_CPP_EXAMPLE_MOTOR_H

#include "Timer.h"

namespace motor {

    class Motor {
    public:
        Motor(timer::Timer16& timer);
        void initialize();
        void setPower(uint8_t power);

    private:
        timer::Timer16& timer_;
    };
}

#endif //AVR_CPP_EXAMPLE_MOTOR_H

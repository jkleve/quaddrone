//
// Created by jesse on 7/9/17.
//

#ifndef AVR_CPP_EXAMPLE_TIMER3_H
#define AVR_CPP_EXAMPLE_TIMER3_H

#include "Ground.h"
#include "Timer.h"

namespace timer {
    class Timer3 : public Timer16 {
    public:
        Timer3();
        ground::Ground& ground_;
    };
}


#endif //AVR_CPP_EXAMPLE_TIMER3_H

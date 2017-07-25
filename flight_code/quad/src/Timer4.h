//
// Created by jesse on 7/19/17.
//

#pragma once

#include "Ground.h"
#include "Timer.h"

namespace timer {
    class Timer4: public Timer16 {
    public:
        Timer4();
        ground::Ground& ground_;
    };
}



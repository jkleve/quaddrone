//
// Created by jesse on 2/20/17.
//
#pragma once

#include "Ground.h"
#include "Timer.h"

namespace timer {
    class Timer1: public Timer16 {
    public:
        Timer1();
        ground::Ground& ground_;
    };
}



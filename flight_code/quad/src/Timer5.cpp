//
// Created by jesse on 7/13/17.
//

#include "Ground.h"
#include "Registers.h"
#include "Timer5.h"
#include "Timer.h"

timer::Timer5::Timer5() :
        Timer16( reg::TIMER5_CONTROL_A,
                 reg::TIMER5_CONTROL_B,
                 reg::TIMER5_CONTROL_C,
                 reg::TIMER5_COUNTER,
                 reg::TIMER5_INPUT_CAPTURE,
                 reg::TIMER5_OUTPUT_COMPARE_A,
                 reg::TIMER5_OUTPUT_COMPARE_B,
                 reg::TIMER5_OUTPUT_COMPARE_C,
                 reg::TIMER5_INT_FLAGS,
                 reg::TIMER5_INT_MASK )
{
}

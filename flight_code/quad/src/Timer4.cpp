//
// Created by jesse on 7/19/17.
//

#include <avr/io.h>

#include "Registers.h"
#include "Timer4.h"

timer::Timer4::Timer4() :
        Timer16( reg::TIMER4_CONTROL_A,
                 reg::TIMER4_CONTROL_B,
                 reg::TIMER4_CONTROL_C,
                 reg::TIMER4_COUNTER,
                 reg::TIMER4_INPUT_CAPTURE,
                 reg::TIMER4_OUTPUT_COMPARE_A,
                 reg::TIMER4_OUTPUT_COMPARE_B,
                 reg::TIMER4_OUTPUT_COMPARE_C,
                 reg::TIMER4_INT_FLAGS,
                 reg::TIMER4_INT_MASK ),
        ground_( ground::Ground::reference() )
{
}


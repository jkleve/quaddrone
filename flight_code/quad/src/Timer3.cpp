//
// Created by jesse on 7/9/17.
//

#include <avr/io.h>

#include "Registers.h"
#include "Timer3.h"

timer::Timer3::Timer3() :
    Timer16( reg::TIMER3_CONTROL_A,
             reg::TIMER3_CONTROL_B,
             reg::TIMER3_CONTROL_C,
             reg::TIMER3_COUNTER,
             reg::TIMER3_INPUT_CAPTURE,
             reg::TIMER3_OUTPUT_COMPARE_A,
             reg::TIMER3_OUTPUT_COMPARE_B,
             reg::TIMER3_OUTPUT_COMPARE_C,
             reg::TIMER3_INT_FLAGS,
             reg::TIMER3_INT_MASK ),
    ground_( ground::Ground::reference() )
{
}

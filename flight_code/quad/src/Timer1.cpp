//
// Created by jesse on 2/20/17.
//

#include <avr/io.h>

#include "Registers.h"
#include "Timer1.h"

timer::Timer1::Timer1() :
        Timer16( reg::TIMER1_CONTROL_A,
                 reg::TIMER1_CONTROL_B,
                 reg::TIMER1_CONTROL_C,
                 reg::TIMER1_COUNTER,
                 reg::TIMER1_INPUT_CAPTURE,
                 reg::TIMER1_OUTPUT_COMPARE_A,
                 reg::TIMER1_OUTPUT_COMPARE_B,
                 reg::TIMER1_OUTPUT_COMPARE_C,
                 reg::TIMER1_INT_FLAGS,
                 reg::TIMER1_INT_MASK ),
        ground_( ground::Ground::reference() )
{
}

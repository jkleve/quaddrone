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
             reg::TIMER3_OUTPUT_COMPARE_C ),
    ground_( ground::Ground::reference() )
{
    _SFR_MEM8(control_a_reg8_) = _BV(WGM31);
    _SFR_MEM8(control_b_reg8_) = _BV(WGM33) | _BV(WGM32);

    ground_.sendRegister(reg::TIMER3_CONTROL_A, TCCR3A);
    ground_.sendRegister(reg::TIMER3_CONTROL_B, TCCR3B);
}

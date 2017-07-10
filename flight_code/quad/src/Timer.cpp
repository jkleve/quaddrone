//
// Created by jesse on 7/9/17.
//

#include "Registers.h"
#include "Timer.h"

timer::Timer16::Timer16( reg::Address control_a_reg,
                reg::Address control_b_reg,
                reg::Address control_c_reg,
                reg::Address counter_reg,
                reg::Address input_capture_reg,
                reg::Address output_compare_a_reg,
                reg::Address output_compare_b_reg,
                reg::Address output_compare_c_reg ) :
    top_( 0 ),
    running_( false ),
    control_a_reg8_( control_a_reg ),
    control_b_reg8_( control_b_reg ),
    control_c_reg8_( control_c_reg ),
    counter_reg16_( counter_reg ),
    input_capture_reg16_( input_capture_reg ),
    output_compare_a_reg16_( output_compare_a_reg ),
    output_compare_b_reg16_( output_compare_b_reg ),
    output_compare_c_reg16_( output_compare_c_reg )
{
    // Set control registers to zeros
    // These should be 0 upon initialization but
    // doesn't hurt
    _SFR_MEM8(control_a_reg8_) = 0;
    _SFR_MEM8(control_b_reg8_) = 0;
    _SFR_MEM8(control_c_reg8_) = 0;
}

void timer::Timer16::set_ms(uint16_t ms)
{
    uint16_t ticks = ms * (F_CPU / 256) / 1000; // 256 is the clk divider
    top_ = ticks;
}

void timer::Timer16::start()
{
    reset();
    running_ = true;
}

bool timer::Timer16::check()
{
    if( running_ )
        return ( (TCNT1 > top_) || ((1 << TOV1) && TIFR1) ); // true if we passed top or have overflowed
    return false;
}

void timer::Timer16::reset()
{
    TIFR1 &= ~(1 << TOV1); // make sure overflow flag is off
    TCNT1 = 0; // reset timer to 0
}


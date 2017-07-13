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
                reg::Address output_compare_c_reg,
                reg::Address interrupt_flag_reg,
                reg::Address interrupt_mask_reg ) :
    top_( 0 ),
    running_( false ),
    mode_( NO_MODE ),
    divider_( 0 ),
    control_a_reg8_( control_a_reg ),
    control_b_reg8_( control_b_reg ),
    control_c_reg8_( control_c_reg ),
    counter_reg16_( counter_reg ),
    input_capture_reg16_( input_capture_reg ),
    output_compare_a_reg16_( output_compare_a_reg ),
    output_compare_b_reg16_( output_compare_b_reg ),
    output_compare_c_reg16_( output_compare_c_reg ),
    interrupt_flag_reg8_( input_capture_reg ),
    interrupt_mask_reg8_( interrupt_mask_reg )
{
    // Set control registers to zeros
    // These should be 0 upon initialization but
    // doesn't hurt
    _SFR_MEM8(control_a_reg8_) = 0;
    _SFR_MEM8(control_b_reg8_) = 0;
    _SFR_MEM8(control_c_reg8_) = 0;
}

bool timer::Timer16::setMs(uint16_t milliseconds)
{
    if (divider_ == 0)
        return false;
    top_ = milliseconds * (F_CPU / divider_) / 1000; // Number of ticks
    return true;
}

void timer::Timer16::start()
{
    reset();
    running_ = true;
}

bool timer::Timer16::check()
{
    if( running_ )
        return ( (_SFR_MEM16(counter_reg16_) > top_) || // Check if we passed top
                 (_SFR_MEM8(interrupt_flag_reg8_) & (1 << TOV1)) ); // Check if we have overflowed
    return false;
}

void timer::Timer16::reset()
{
    _SFR_MEM8(interrupt_flag_reg8_) &= _BV(TOV1); // Make sure overflow flag is off
    _SFR_MEM16(counter_reg16_) = 0; // Reset timer to 0
}

void timer::Timer16::setNormalMode()
{
    // Clear WGMx0, WGMx1, WGMx2, & WGMx3
    _SFR_MEM8(control_a_reg8_) &= (~_BV(WGM11) & ~_BV(WGM10)); // TODO make our own WGM values to specify the 16 bit WGMs
    _SFR_MEM8(control_b_reg8_) &= (~_BV(WGM13) & ~_BV(WGM12));

    mode_ = NORMAL;
}

void timer::Timer16::setOutputCompare(OutputCompareMode mode)
{

}

void timer::Timer16::disableOutputCompare()
{
    // Clear COMnA0 & COMnA1
    _SFR_MEM8(control_a_reg8_) &= (~_BV(COM1A1) & ~_BV(COM1A0));
}

void timer::Timer16::setPrescaler(Prescaler prescaler)
{
    switch (prescaler) {
        case PRESCALE1: // 0b001
            _SFR_MEM8(control_b_reg8_) &= ~_BV(CS12) & ~_BV(CS11);
            _SFR_MEM8(control_b_reg8_) |= _BV(CS10);
            divider_ = 1;
            break;
        case PRESCALE8: // 0b010
            _SFR_MEM8(control_b_reg8_) &= ~_BV(CS12) & ~_BV(CS10);
            _SFR_MEM8(control_b_reg8_) |= _BV(CS11);
            divider_ = 8;
            break;
        case PRESCALE64: // 0b011
            _SFR_MEM8(control_b_reg8_) &= ~_BV(CS12);
            _SFR_MEM8(control_b_reg8_) |= _BV(CS11) | _BV(CS10);
            divider_ = 64;
            break;
        case PRESCALE256: // 0b100
            _SFR_MEM8(control_b_reg8_) &= ~_BV(CS11) & _BV(CS10);
            _SFR_MEM8(control_b_reg8_) |= _BV(CS12);
            divider_ = 256;
            break;
        case PRESCALE1024: // 0b101
            _SFR_MEM8(control_b_reg8_) &= ~_BV(CS11);
            _SFR_MEM8(control_b_reg8_) |= _BV(CS12) | _BV(CS10);
            divider_ = 1024;
            break;
        case EXTERNAL_ON_FALLING_EDGE: // 0b110
            _SFR_MEM8(control_b_reg8_) &= ~_BV(CS10);
            _SFR_MEM8(control_b_reg8_) |= _BV(CS12) | _BV(CS11);
            divider_ = 0;
            break;
        case EXTERNAL_ON_RISING_EDGE: // 0b111
            _SFR_MEM8(control_b_reg8_) |= _BV(CS12) | _BV(CS11) | _BV(CS10);
            divider_ = 0;
            break;
        case PRESCALE_NONE: // 0b000
        default:
            _SFR_MEM8(control_b_reg8_) &= ~_BV(CS12) & ~_BV(CS11) & ~_BV(CS10);
            divider_ = 0;
            break;
    }
}

uint16_t timer::Timer16::getTime() {
    return _SFR_MEM16(counter_reg16_);
}

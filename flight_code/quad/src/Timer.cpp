//
// Created by jesse on 7/9/17.
//

#include "Registers.h"
#include "Timer.h"
#include "Ground.h"

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
    interrupt_mask_reg8_( interrupt_mask_reg ),
    ground_( ground::Ground::reference() )
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

uint16_t timer::Timer16::millis(bool restart) {
    // TODO this method doesn't have the greatest resolution
    // TODO if you want to know when 1 second is up at 256 prescaler
    // TODO you'll have to wait until 1.024 seconds because of integer
    // TODO math. could convert to uint32_t and use F_CPU instead of kilo hz
    // TODO or use floating point math. would need to test how much slower
    // TODO this would cause this method. This method needs to be fast though
    // TODO if it's going to be used a decent amount by the rambo/I2C
    if (restart)
        reset();

    uint16_t ms = (_SFR_MEM16(counter_reg16_) / F_CPU_KILO_HZ) * divider_; // TODO we could refactor to get this calculation done once, then it'd be a lot quicker
    //ground_.sendRegister(reg::TIMER5_COUNTER, _SFR_MEM16(counter_reg16_), _SFR_MEM16(counter_reg16_) >> 8);

    //ground_.sendWord(ms);
    //ground_.sendString("Divider is ...");
    //ground_.sendWord(divider_);
    //ground_.sendWord(F_CPU_KILO_HZ);
    //ground_.sendWord(_SFR_MEM16(counter_reg16_));

    return ms;
}

void timer::Timer16::setMode(timer::Mode mode)
{
    // Turn off all mode bits to make it easy to set mode
    _SFR_MEM8(control_a_reg8_) = _SFR_MEM8(control_a_reg8_) &
                                 ~(_BV(WGM31) | _BV(WGM30));
    _SFR_MEM8(control_b_reg8_) = _SFR_MEM8(control_b_reg8_) &
                                 ~(_BV(WGM33) | _BV(WGM32));

    switch (mode) {
        case FAST_PWM:
            _SFR_MEM8(control_a_reg8_) |= _BV(WGM31);
            _SFR_MEM8(control_b_reg8_) |= _BV(WGM33) | _BV(WGM32);
            break;
        default:
            break;
    }
}

bool timer::Timer16::setFastPwm(uint8_t frequency)
{
    ground_.sendString("Frequency is");
    ground_.sendByte(frequency);
    uint16_t n = 0;
    uint32_t temp = 65536;
    uint32_t prescaler = (uint32_t) ((uint32_t)F_CPU /
                                     (uint32_t)frequency /
                                     temp);
    setMode(FAST_PWM);

    // Turn off all prescaler bits to make it easy to set
    _SFR_MEM8(control_b_reg8_) = _SFR_MEM8(control_b_reg8_) &
                                 ~(_BV(CS32) | _BV(CS31) | _BV(CS30));
    // Turn off all output compare bits to make it easy to set
    _SFR_MEM8(control_a_reg8_) = _SFR_MEM8(control_a_reg8_) &
                                 ~(_BV(COM3A1) | _BV(COM3A0) |
                                   _BV(COM3B1) | _BV(COM3B0) |
                                   _BV(COM3C1) | _BV(COM3C0));

    ground_.sendString("Here");
    ground_.send32(F_CPU);
    ground_.send32(temp);
    ground_.sendByte(static_cast<uint8_t>(prescaler));
    ground_.sendWord(static_cast<uint16_t>(prescaler));
    ground_.send32(prescaler);
    ground_.sendString("----");

    if (prescaler < 1) {
        _SFR_MEM8(control_b_reg8_) |= _BV(CS30);
        ground_.sendString("1");
        n = 1;
    }
    else if (prescaler < 8) {
        _SFR_MEM8(control_b_reg8_) |= _BV(CS31);
        ground_.sendString("8");
        n = 8;
    }
    else if (prescaler < 64) {
        _SFR_MEM8(control_b_reg8_) |= _BV(CS31) | _BV(CS30);
        ground_.sendString("64");
        n = 64;
    }
    else if (prescaler < 256) {
        _SFR_MEM8(control_b_reg8_) |= _BV(CS32);
        ground_.sendString("256");
        n = 256;
    }
    else if (prescaler < 1024) {
        _SFR_MEM8(control_b_reg8_) |= _BV(CS32) | _BV(CS30);
        ground_.sendString("1024");
        n = 1024;
    }
    else {
        ground_.sendString("None :(");
        return false; // 16 bit timer can't handle requested frequency
    }

    top_ = static_cast<uint16_t>( ( ( (uint32_t)F_CPU ) / (uint32_t)frequency / n) - 1 );
    _SFR_MEM16(input_capture_reg16_) = top_;
    _SFR_MEM16(output_compare_a_reg16_) = 0;
    ground_.sendString("Setting top_ to:");
    ground_.sendWord(top_);

    // TODO move this to different method?
    _SFR_MEM8(control_a_reg8_) |= _BV(COM3A1); // Set output compare A to clear on input compare match

    return true;
}

void timer::Timer16::setDuty(float duty)
{
    ground_.sendWord(top_);
    uint16_t tmp = static_cast<uint16_t>(duty/100.0 * top_);
    ground_.sendWord(tmp);
    _SFR_MEM16(output_compare_a_reg16_) = tmp;
}


//
// Created by jesse on 7/9/17.
//

#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

namespace timer {
    enum Timer {
        TIMER0,
        TIMER1,
        TIMER2,
        TIMER3,
        TIMER4,
        TIMER5
    };

    enum Prescaler {
        NONE,
        PRESCALE1,
        PRESCALE8,
        PRESCALE64,
        PRESCALE256,
        PRESCALE1024,
        EXTERNAL_ON_FALLING_EDGE,
        EXTERNAL_ON_RISING_EDGE
    };

    class Timer16 {
    public:
        void set_ms(uint16_t); // max is a decent amount less than 2000 ms. Otherwise
        // we need to divide the clock by 1024 instead
        void start();
        bool check();
        void reset();

    protected:
        Timer16( reg::Address, // control a
                 reg::Address, // control b
                 reg::Address, // control c
                 reg::Address, // counter
                 reg::Address, // input capture
                 reg::Address, // output compare a
                 reg::Address, // output compare b
                 reg::Address  // output compare c
               );

        // Member variables
        uint16_t top_;
        bool running_;

        // Pointer holders
        uint8_t control_a_reg8_;
        uint8_t control_b_reg8_;
        uint8_t control_c_reg8_;
        uint16_t counter_reg16_;
        uint8_t input_capture_reg16_;
        uint8_t output_compare_a_reg16_;
        uint8_t output_compare_b_reg16_;
        uint8_t output_compare_c_reg16_;
    };
}


#endif // TIMER_H

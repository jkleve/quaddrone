//
// Created by jesse on 7/9/17.
//

#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include "Ground.h"

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
        PRESCALE_NONE,
        PRESCALE1,
        PRESCALE8,
        PRESCALE64,
        PRESCALE256,
        PRESCALE1024,
        EXTERNAL_ON_FALLING_EDGE,
        EXTERNAL_ON_RISING_EDGE
    };

    enum Mode {
        NO_MODE,
        NORMAL,
        CTC,
        FAST_PWM
    };

    enum OutputCompareMode {
        DISCONNECT_A,
        DISCONNECT_B,
        DISCONNECT_C,
        TOGGLE_A,
        TOGGLE_B,
        TOGGLE_C,
        CLEAR_A,
        CLEAR_B,
        CLEAR_C,
        SET_A,
        SET_B,
        SET_C
    };

    class Timer16 {
    public:
        static const uint16_t F_CPU_KILO_HZ= F_CPU / 1000;

        bool setMs(uint16_t); // max is a decent amount less than 2000 ms. Otherwise
        // we need to divide the clock by 1024 instead
        void start();
        bool check();
        void reset();
        uint16_t millis(bool restart = false);
        void setMode(Mode mode);
        void setNormalMode();
        bool setFastPwm(uint8_t frequency);
        void setDuty(float duty);
        void setDutyA(float duty);
        void setDutyB(float duty);
        void setDutyC(float duty);
        void disableOutputCompare(); // TODO temporary
        void setOutputCompare(OutputCompareMode mode);
        void setPrescaler(Prescaler prescaler);
        uint16_t getTime();

    protected:
        Timer16( reg::Address, // control a
                 reg::Address, // control b
                 reg::Address, // control c
                 reg::Address, // counter
                 reg::Address, // input capture
                 reg::Address, // output compare a
                 reg::Address, // output compare b
                 reg::Address, // output compare c
                 reg::Address, // interrupt flag
                 reg::Address  // timer mask
               );

        // Member variables
        uint16_t top_;
        bool running_;
        Mode mode_;
        uint16_t divider_;

        // Pointer holders
        //uint8_t control_a_reg8_;
        //uint8_t control_b_reg8_;
        //uint8_t control_c_reg8_;
        //uint16_t counter_reg16_; // counter addresses need 2 bytes
        //uint8_t input_capture_reg16_;
        //uint8_t output_compare_a_reg16_;
        //uint8_t output_compare_b_reg16_;
        //uint8_t output_compare_c_reg16_;
        //uint8_t interrupt_flag_reg8_;
        //uint8_t interrupt_mask_reg8_;

        uint16_t control_a_reg8_; // temporary until I decide what to do about timer5's register addresses being 2 bytes
        uint16_t control_b_reg8_;
        uint16_t control_c_reg8_;
        uint16_t counter_reg16_; // counter addresses need 2 bytes
        uint16_t input_capture_reg16_;
        uint16_t output_compare_a_reg16_;
        uint16_t output_compare_b_reg16_;
        uint16_t output_compare_c_reg16_;
        uint16_t interrupt_flag_reg8_;
        uint16_t interrupt_mask_reg8_;

        ground::Ground& ground_;
    };
}


#endif // TIMER_H

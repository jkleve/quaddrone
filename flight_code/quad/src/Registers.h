//
// Created by jesse on 6/30/17.
//

#ifndef REGISTERS_H
#define REGISTERS_H

#include <avr/io.h>

namespace reg {
    enum Address {
        // Timer interrupt flag registers
        TIMER3_INT_FLAGS = 0x18,

        // Timer mask registers
        TIMER0_INT_MASK = 0x6E, // TIMSK0
        TIMER1_INT_MASK = 0x6F, // TIMSK1
        TIMER2_INT_MASK = 0x70, // TIMSK2
        TIMER3_INT_MASK = 0x71, // TIMSK3

        // Timer 3 registers
        TIMER3_CONTROL_A        = 0x90, // TCCR3A
        TIMER3_CONTROL_B        = 0x91, // TCCR3B
        TIMER3_CONTROL_C        = 0x92, // TCCR3C
        TIMER3_COUNTER          = 0x94, // TCNT3
        TIMER3_INPUT_CAPTURE    = 0x96, // ICR3
        TIMER3_OUTPUT_COMPARE_A = 0x98, // OCR3A
        TIMER3_OUTPUT_COMPARE_B = 0x9A, // OCR3B
        TIMER3_OUTPUT_COMPARE_C = 0x9C, // OCR3C

        // Twi
        TWI_BIT_RATE   = 0xB8,
        REG_TWI_STATUS = 0xB9,
        TWI_CONTROL    = 0xBC,
        TWI_DATA       = 0xBB,

        // Timer 5
        TIMER5_CONTROL_A = 0x120,
        TIMER5_CONTROL_B = 0x121,
        TIMER5_CONTROL_C = 0x122,
        TIMER5_COUNTER = 0x124,
        TIMER5_INPUT_CAPTURE = 0x126,
        TIMER5_OUTPUT_COMPARE_A = 0x128,
        TIMER5_OUTPUT_COMPARE_B = 0x12A,
        TIMER5_OUTPUT_COMPARE_C = 0x12C
    };
}

#endif // REGISTERS_H

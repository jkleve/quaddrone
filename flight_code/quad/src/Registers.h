//
// Created by jesse on 6/30/17.
//

#ifndef REGISTERS_H
#define REGISTERS_H

#include <avr/io.h>

namespace reg {
    enum Address {
        // Timer interrupt flag registers
        TIMER0_INT_FLAGS = 0x35, // TIFR0
        TIMER1_INT_FLAGS = 0x36, // TIFR1
        TIMER2_INT_FLAGS = 0x37, // TIFR2
        TIMER3_INT_FLAGS = 0x38, // TIFR3
        TIMER4_INT_FLAGS = 0x39, // TIFR4
        TIMER5_INT_FLAGS = 0x3A, // TIFR5

        // Timer mask registers
        TIMER0_INT_MASK = 0x6E, // TIMSK0
        TIMER1_INT_MASK = 0x6F, // TIMSK1
        TIMER2_INT_MASK = 0x70, // TIMSK2
        TIMER3_INT_MASK = 0x71, // TIMSK3
        TIMER4_INT_MASK = 0x72, // TIMSK4
        TIMER5_INT_MASK = 0x73, // TIMSK5

        // Timer 1 registers
        TIMER1_CONTROL_A        = 0x80, // TCCR1A
        TIMER1_CONTROL_B        = 0x81, // TCCR1B
        TIMER1_CONTROL_C        = 0x82, // TCCR1C
        TIMER1_COUNTER          = 0x84, // TCNT1
        TIMER1_INPUT_CAPTURE    = 0x86, // ICR1
        TIMER1_OUTPUT_COMPARE_A = 0x88, // OCR1A
        TIMER1_OUTPUT_COMPARE_B = 0x8A, // OCR1B
        TIMER1_OUTPUT_COMPARE_C = 0x8C, // OCR1C

        // Timer 3 registers
        TIMER3_CONTROL_A        = 0x90, // TCCR3A
        TIMER3_CONTROL_B        = 0x91, // TCCR3B
        TIMER3_CONTROL_C        = 0x92, // TCCR3C
        TIMER3_COUNTER          = 0x94, // TCNT3
        TIMER3_INPUT_CAPTURE    = 0x96, // ICR3
        TIMER3_OUTPUT_COMPARE_A = 0x98, // OCR3A
        TIMER3_OUTPUT_COMPARE_B = 0x9A, // OCR3B
        TIMER3_OUTPUT_COMPARE_C = 0x9C, // OCR3C

        // Timer 4 registers
        TIMER4_CONTROL_A        = 0xA0, // TCCR4A
        TIMER4_CONTROL_B        = 0xA1, // TCCR4B
        TIMER4_CONTROL_C        = 0xA2, // TCCR4C
        TIMER4_COUNTER          = 0xA4, // TCNT4
        TIMER4_INPUT_CAPTURE    = 0xA6, // ICR4
        TIMER4_OUTPUT_COMPARE_A = 0xA8, // OCR4A
        TIMER4_OUTPUT_COMPARE_B = 0xAA, // OCR4B
        TIMER4_OUTPUT_COMPARE_C = 0xAc, // OCR4C

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

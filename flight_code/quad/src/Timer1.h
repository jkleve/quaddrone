//
// Created by jesse on 2/20/17.
//

#ifndef AVR_CPP_EXAMPLE_TIMER1_H
#define AVR_CPP_EXAMPLE_TIMER1_H

#include <stdint.h>

class Timer1 {
    public:
        static Timer1& reference();
        void set_ms(uint16_t); // max is a decent amount less than 2000 ms. Otherwise
                               // we need to divide the clock by 1024 instead
        void start();
        bool check();
        void reset();
    private:
        Timer1();
        uint16_t top;
        bool running;
};


#endif //AVR_CPP_EXAMPLE_TIMER1_H

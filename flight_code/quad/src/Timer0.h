//
// Created by jesse on 2/21/17.
//

#ifndef AVR_CPP_EXAMPLE_TIMER0_H
#define AVR_CPP_EXAMPLE_TIMER0_H

#include <stdint.h>

class Timer0 {
    public:
        static Timer0& reference();
        bool check();
        void reset();
    private:
        Timer0();
        uint8_t top;
};


#endif //AVR_CPP_EXAMPLE_TIMER0_H

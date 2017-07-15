//
// Created by jesse on 7/14/17.
//

#pragma once

#include "Ground.h"
#include "Timer.h"

namespace serial {

    enum SerialType {
        HEX,
        DEC
    };

    class SerialWrapper {
    public:
        SerialWrapper(ground::Ground& ground);
        void print(const char* string);
        void println(const char* string);
        void println();
        void println(int8_t data);
        void println(uint16_t data);
        void println(uint8_t data, SerialType type);
        void print(uint8_t data, SerialType type);
    private:
        ground::Ground& ground_;
    };

    extern serial::SerialWrapper Serial;
}

namespace timer {
    void setMillisTimer(Timer16 timer);
    uint16_t millis();
    void delay(uint8_t milliseconds);
}
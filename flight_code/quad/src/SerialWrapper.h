//
// Created by jesse on 7/14/17.
//

#pragma once

#include "Ground.h"

namespace serial {

    enum SerialType {
        HEX,
        DEC
    };

    class SerialWrapper {
    public:
        SerialWrapper(ground::Ground& ground);
        void print(const char *string);
        void print(uint8_t data, SerialType type);
    private:
        ground::Ground& ground_;
    };

    extern serial::SerialWrapper Serial;
}

//
// Created by jesse on 7/14/17.
//

#include "SerialWrapper.h"

serial::SerialWrapper serial::Serial = serial::SerialWrapper(ground::Ground::reference());

serial::SerialWrapper::SerialWrapper(ground::Ground& ground) : ground_( ground )
{

}

void serial::SerialWrapper::print(const char *string)
{
    ground_.sendString(string);
}

void serial::SerialWrapper::print(uint8_t data, serial::SerialType type)
{
    switch (type) {
        case HEX:
        case DEC:
        default:
            ground_.sendByte(data);
            break;
    }
}


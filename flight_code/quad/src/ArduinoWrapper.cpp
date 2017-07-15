//
// Created by jesse on 7/14/17.
//

extern "C" {
#include <util/delay.h>
}

#include "ArduinoWrapper.h"

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

void serial::SerialWrapper::println(const char* string)
{
    print(string);
}

void serial::SerialWrapper::println()
{
    print("");
}

void serial::SerialWrapper::println(uint8_t data, serial::SerialType type)
{
    print(data, type);
}

void serial::SerialWrapper::println(int8_t data)
{
    print(data, HEX);
}

void serial::SerialWrapper::println(uint16_t data)
{
    ground_.sendWord(data);
}


///////////
// Timer //
///////////

// Namespace global functions
void timer::setMillisTimer(timer::Timer16 timer)
{
    // TODO this should set a timer, then when millis() is called, that timers millis() will be checked
    timer.setNormalMode();
    timer.disableOutputCompare();
    timer.setPrescaler(timer::PRESCALE256);
}

uint16_t timer::millis()
{
    // TODO this will currently never cause a timeout which will be fine for testing
    return 0;
}

void timer::delay(uint8_t milliseconds)
{
    // _delay_ms needs to have a constant value as its parameter.
    // If it does not, then it will complain at compile time.
    // Looping through the number of milliseconds and delaying
    // 1 each time is a simple work around.
    for (uint8_t i = 0; i < milliseconds; i++) {
        _delay_ms(1);
    }
}

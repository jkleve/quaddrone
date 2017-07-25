//
// Created by jesse on 7/16/17.
//

#include "Motor.h"

//motor::Motor::Motor(timer::Timer16 &timer) : timer_( timer )
motor::Motor::Motor()
{
    //DDRB = (1 << DDB5); // Set PB5 as output
    //timer_.setFastPwm(50); // Typical ESC expects a 50 Hz signal
}

void motor::Motor::initialize()
{
    //setPower(100);
}

float motor::Motor::getDuty(uint8_t power)
{
    // This method could be quicker if the math was using
    // integers instead of floats

    // Typical ESC expects a duty cycle of 5% (0 power) to
    // 10% (100 power). I dropped the 5% down a bit
    float duty = 4.245 + power * 0.05;
    return duty;
    //timer_.setDuty(duty);
}

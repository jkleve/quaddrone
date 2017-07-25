//
// Created by jesse on 7/19/17.
//

#include "MotorManager.h"

//              --------------------------------------------------------
//        PG5 -| o <- Index corner                                      |
//        PE0 -|                                                        |
//        PE1 -|                                                        |
//        PE2 -|                                                        |
// (OC3A) PE3 -| (Connected to OUTPUT 8)                                |
// (OC3B) PE4 -| (Connected to OUTPUT 7)                                |
// (OC3C) PE5 -| (Connected to OUTPUT 6)                                |
//        PE6 -|                                                        |
//        PE7 -|                                                        |
//        VCC -|                                                        |
//        GND -|                      /\\      //\                      |
//        PH0 -|                     /__\\    //_/                      |
//        PH1 -|                    /    \\  // \                       |
//        PH2 -|                           \/                           |
// (OC4A) PH3 -| (Connected to OUTPUT 5)                                |
// (OC4B) PH4 -| (Connected to OUTPUT 4) Motor 4                        |
// (OC4C) PH5 -| (Connected to OUTPUT 3) Motor 3                        |
// (OC2B) PH6 -|                                                        |
//        PB0 -|                                                        |
//        PB1 -|                                                        |
//        PB2 -|                                                        |
//        PB3 -|                                                        |
// (OC2A) PB4 -|                                                        |
// (OC1A) PB5 -| (Connected to OUTPUT 2) Motor 2                        |
// (OC1B) PB6 -| (Connected to OUTPUT 1) Motor 1                        |
//              --------------------------------------------------------

motor::MotorManager::MotorManager(timer::Timer16& timer1, timer::Timer16& timer2) :
    timer1_( timer1 ), timer2_( timer2 ), fl_motor_( Motor() ), fr_motor_( Motor() ),
    bl_motor_( Motor() ), br_motor_( Motor() )
{
    // TODO should these be in timer when we set output compare
    // TODO or in quadMgr in the constructor?
    // TODO if in timer, add to register class. or either way do it?
    DDRB |= _BV(DDB6); // Set PB5 as output for motor 1
    DDRB |= _BV(DDB5); // Set PB5 as output for motor 2
    DDRH |= _BV(DDH5); // Set PB5 as output for motor 3
    DDRH |= _BV(DDH4); // Set PB5 as output for motor 4

    timer1_.setFastPwm(50); // The ESCs expect a 50 Hz PWM frequency
    timer2_.setFastPwm(50);

    timer1_.setOutputCompare(timer::CLEAR_A); // motor 2
    timer1_.setOutputCompare(timer::CLEAR_B); // motor 1
    timer1_.setOutputCompare(timer::DISCONNECT_C);

    timer2_.setOutputCompare(timer::DISCONNECT_A);
    timer2_.setOutputCompare(timer::CLEAR_B); // motor 4
    timer2_.setOutputCompare(timer::CLEAR_C); // motor 3
}

void motor::MotorManager::setPower(motor::MotorSelect motor, uint8_t power)
{
    ground::Ground& ground = ground::Ground::reference();
    // TODO don't necessarily like how many times I have to remember which motor is on which
    // TODO output compare channel and on what timer
    switch (motor) {
        case MOTOR1:
            timer1_.setDutyB( fl_motor_.getDuty(power) );
            break;
        case MOTOR2:
            timer1_.setDutyA( fr_motor_.getDuty(power) );
            break;
        case MOTOR3:
            timer2_.setDutyC( bl_motor_.getDuty(power) );
            break;
        case MOTOR4:
            timer2_.setDutyB( br_motor_.getDuty(power) );
            break;
        case ALL_MOTORS:
            ground.sendByte(power);
            setPower(MOTOR1, power);
            setPower(MOTOR2, power);
            setPower(MOTOR3, power);
            setPower(MOTOR4, power);
            break;
        default:
            break;
    }
}

void motor::MotorManager::initialize(MotorSelect motor)
{
    setPower(motor, 100);
}

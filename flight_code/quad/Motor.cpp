//
// Created by jesse on 7/10/17.
//

#include "Motor.h"
#include "Timer.h"

motor::Motor::Motor(timer::Timer16& timer) : timer_( timer ), power_( 0 )
{

}

//
// Created by jesse on 7/26/17.
//

#pragma once

#include <stdio.h>

namespace quad {

    class UserInput {
    public:
        UserInput();

        uint8_t yaw;
        uint8_t pitch;
        uint8_t roll;
        uint8_t throttle;
    };
}


//
// Created by jesse on 6/27/17.
//

#ifndef MPU_H
#define MPU_H

//#include "I2Cdev.h" // Where is this?

#include "MPU6050_6Axis_MotionApps20.h"

namespace mpu {

    class MpuMgr {
    public:
        MpuMgr(uint8_t address);
    private:
        uint8_t address;
        MPU6050 mpu;
    };
}

#endif // MPU_H

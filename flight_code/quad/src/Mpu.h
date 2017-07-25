//
// Created by jesse on 6/27/17.
//

#pragma once

#include "Ground.h"
#include "MPU6050.h"

namespace mpu {

    class MpuMgr {
    public:
        MpuMgr(ground::Ground&);
        uint8_t getQuaternion(Quaternion&);
    private:
        MPU6050 mpu_;
        ground::Ground& ground_;
        bool initialized_;
    };
}


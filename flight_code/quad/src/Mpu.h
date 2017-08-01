//
// Created by jesse on 6/27/17.
//

#pragma once

#include "Ground.h"
#include "MPU6050.h"

namespace mpu {

    //typedef uint8_t[32] MpuPacket;

    class MpuMgr {
    public:
        MpuMgr(ground::Ground&);
        uint8_t getQuaternion(Quaternion&);
        uint8_t getYawPitchRoll(double[3]);
    private:
        uint8_t getMpuPacket();

        MPU6050 mpu_;
        ground::Ground& ground_;
        bool initialized_;
        VectorFloat gravity_;
        Quaternion quaternion_;
    };
}


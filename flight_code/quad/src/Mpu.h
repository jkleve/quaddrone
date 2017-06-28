#include "I2Cdev.h" // Where is this?

#include "MPU6050_6Axis_MotionApps20.h"

namespace mpu {
    
    class MpuMgr {

        MpuMgr() {
            mpu.initialize();

            uint8_t devStatus = mpu.dmpInitialize();

            if (devStatus == 0) {
                mpu.setDMPEnabled(true);
            }
            else {
                // failed to initialize
            }
        }

        MPU6050 mpu;
    };

}

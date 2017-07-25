//
// Created by jesse on 6/27/17.
//

#include <stdio.h>

#include "Ground.h"
#include "Mpu.h"
#include "MPU6050.h"
#include "MPU6050_6Axis_MotionApps20.h"

mpu::MpuMgr::MpuMgr( ground::Ground& ground ) : mpu_( MPU6050() ), ground_( ground ), initialized_( false )
{
    uint8_t devStatus = 0;      // return status after each device operation (0 = success, !0 = error)

    // orientation/motion vars
    //Quaternion q;           // [w, x, y, z]         quaternion container
    //char quatString[21];
    //VectorInt16 aa;         // [x, y, z]            accel sensor measurements
    //VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
    //VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
    //VectorFloat gravity;    // [x, y, z]            gravity vector
    //float euler[3];         // [psi, theta, phi]    Euler angle container
    //float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

    mpu_.initialize();

    // verify connection
    ground_.sendString("Testing device connections...");
    ground_.sendString(mpu_.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    devStatus = mpu_.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    //mpu.setXGyroOffset(220);
    //mpu.setYGyroOffset(76);
    //mpu.setZGyroOffset(-85);
    //mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        Serial.println("Enabling DMP...");
        mpu_.setDMPEnabled(true);

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        Serial.println("DMP ready!");
        initialized_ = true;

        // get expected DMP packet size for later comparison
        //packetSize = mpu_.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print("DMP Initialization failed code:");
        Serial.print(devStatus, DEC);
    }
}

// 0: Success
// 1: Not initialized
// 2: Not a full packet (42 bytes) in FIFO buffer
// 3: FIFO overflow
uint8_t mpu::MpuMgr::getQuaternion(Quaternion& quaternion)
{
    uint16_t packetSize = 0;    // expected DMP packet size (default is 42 bytes)
    uint16_t fifoCount;     // count of all bytes currently in FIFO
    uint8_t fifoBuffer[64]; // FIFO storage buffer

    if (initialized_) {
        // get current FIFO count
        fifoCount = mpu_.getFIFOCount();

        // check for overflow (this should never happen unless our code is too inefficient)
        if (fifoCount == 1024) {
            // reset so we can continue cleanly
            mpu_.resetFIFO();
            Serial.println("FIFO overflow!");
            return 3;
        }
        else { // otherwise, check for DMP data ready interrupt (this should happen frequently)
            // wait for correct available data length, should be a VERY short wait
            if (mpu_.getFIFOCount() < packetSize)
                return 2;

            // read a packet from FIFO
            mpu_.getFIFOBytes(fifoBuffer, packetSize);

            // track FIFO count here in case there is > 1 packet available
            // (this lets us immediately read more without waiting for an interrupt)
            fifoCount -= packetSize;

            // display quaternion values in easy matrix form: w x y z
            mpu_.dmpGetQuaternion(&quaternion, fifoBuffer);

            //sprintf(quatString, "%.2f,%.2f,%.2f,%.2f", q.w, q.x, q.y, q.z);
            //ground_.sendQuaternion(quatString);

            return 0;
        }
    }
    return 1;
}

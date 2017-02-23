//
// Created by jesse on 2/22/17.
//

#include "ImuMgr.h"
#include "TwiMgr.h"

IMU::ImuMgr::ImuMgr() :
    twi( Twi::TwiMgr::reference() ),
    devAddr( MPU::DEFAULT_ADDR )
{
    setClockSource(MPU6050_CLOCK_PLL_XGYRO);
    setFullScaleGyroRange(MPU6050_GYRO_FS_250);
    setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
    setSleepEnabled(false); // thanks to Jack Elston for pointing this one out!
}

IMU::ImuMgr &IMU::ImuMgr::reference( void )
{
    static IMU::ImuMgr ref;
    return ref;
}

void IMU::ImuMgr::setClockSource(uint8_t source)
{
    twi.writeBits(devAddr, MPU::PWR_MGMT_REG, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source);
}

void IMU::ImuMgr::setFullScaleGyroRange(uint8_t range)
{
    twi.writeBits(devAddr, MPU::GYRO_CONFIG_REG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);
}

void IMU::ImuMgr::setFullScaleAccelRange(uint8_t range)
{
    twi.writeBits(devAddr, MPU::ACCEL_CONFIG_REG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);
}

void IMU::ImuMgr::setSleepEnabled(bool enabled)
{
    twi.writeBit(devAddr, MPU::PWR_MGMT_REG, MPU6050_PWR1_SLEEP_BIT, enabled);
}
//
// Created by jesse on 2/22/17.
//

#include "ImuMgr.h"
#include "TwiMgr.h"

imu::ImuMgr::ImuMgr() :
    twi( twi::TwiMgr::reference() ),
    devAddr( mpu::DEFAULT_ADDR )
{
//    setClockSource(MPU6050_CLOCK_PLL_XGYRO);
//    setFullScaleGyroRange(MPU6050_GYRO_FS_250);
//    setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
    setSleepEnabled(false); // thanks to Jack Elston for pointing this one out!
}

imu::ImuMgr &imu::ImuMgr::reference( void )
{
    static imu::ImuMgr ref;
    return ref;
}

//void imu::ImuMgr::setClockSource(uint8_t source)
//{
//    twi.writeBits(devAddr, mpu::PWR_MGMT_REG, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source);
//}
//
//void imu::ImuMgr::setFullScaleGyroRange(uint8_t range)
//{
//    twi.writeBits(devAddr, mpu::GYRO_CONFIG_REG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);
//}
//
//void imu::ImuMgr::setFullScaleAccelRange(uint8_t range)
//{
//    twi.writeBits(devAddr, mpu::ACCEL_CONFIG_REG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);
//}

void imu::ImuMgr::setSleepEnabled(bool enabled)
{
    twi.writeBit(devAddr, mpu::PWR_MGMT_REG, mpu::PWR_SLEEP_BIT, enabled);
}
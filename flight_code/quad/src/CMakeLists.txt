#####################################################################
# simple AVR executable
#####################################################################
add_avr_executable(
   quad
   main.cpp
   CommsMgr.cpp
   Eeprom.cpp
   Ground.cpp
   QuadState.cpp
   QuadMgr.cpp
   QuadParams.cpp
   I2C.cpp
   I2Cdev.cpp
   #InterruptMgr.cpp
   LedMgr.cpp
   Motor.cpp
   MotorManager.cpp
   MPU6050.cpp
   MPU6050_6Axis_MotionApps20.h
   Mpu.cpp
   ArduinoWrapper.cpp
   Timer.cpp
   Timer0.cpp
   Timer1.cpp
   Timer3.cpp
   Timer4.cpp
   Timer5.cpp
   #ImuMgr.cpp
   )

#####################################################################
# libraries to link to
#####################################################################
#target_link_libraries()
  # toggle-led-cpp-${AVR_MCU}.elf
  # mycpplib-${AVR_MCU}
  # )

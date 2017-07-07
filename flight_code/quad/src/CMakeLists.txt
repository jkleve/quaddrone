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
   InterruptMgr.cpp
   LedMgr.cpp
   #Mpu.cpp
   Timer1.cpp
   Timer0.cpp
   TwiMgr.cpp
   #ImuMgr.cpp
   )

#####################################################################
# libraries to link to
#####################################################################
#target_link_libraries()
  # toggle-led-cpp-${AVR_MCU}.elf
  # mycpplib-${AVR_MCU}
  # )

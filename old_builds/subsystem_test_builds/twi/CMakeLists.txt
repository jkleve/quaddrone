cmake_minimum_required(VERSION 3.6)
project(twi)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/addr_test/addr_test.c
        src/addr_test/comm.c
        src/addr_test/comm.h
        src/addr_test/MPU6050.c
        src/addr_test/MPU6050.h
        src/addr_test/twi.c
        src/addr_test/twi.h
        src/addr_test/twi_master.c
        src/addr_test/twi_master.h
        src/addr_test/usart.c
        src/addr_test/usart.h
        src/comm.c
        src/comm.h
        src/DCM.c
        src/DCM.h
        src/main.c
        src/mpu.c
        src/MPU6050.c
        src/MPU6050.h
        src/PID.c
        src/PID.h
        src/test.c
        src/twi_master.c
        src/twi_master.h
        src/usart.c
        src/usart.h
        QuadcopterV6.c
        twitest.c)

add_executable(twi ${SOURCE_FILES})
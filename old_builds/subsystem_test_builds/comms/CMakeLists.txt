cmake_minimum_required(VERSION 3.6)
project(comms)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        comm.c
        comm.h
        main.c)

include_directories(../include)

add_executable(comms ${SOURCE_FILES})
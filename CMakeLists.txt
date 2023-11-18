cmake_minimum_required(VERSION 3.22)
project(Scheduler)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(Scheduler main.cpp Wrappers.h Solver.cpp Solver.h
        Wrappers.cpp)

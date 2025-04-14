cmake_minimum_required(VERSION 3.31)
project(BookingSystem)

set(CMAKE_CXX_STANDARD 14)

include_directories(businessLogicLayer)
include_directories(dataAccessLayer)

add_executable(BookingSystem
        src/app.cpp
        include/app.h
        src/mainMenu.cpp
        include/mainMenu.h
        src/main.cpp)

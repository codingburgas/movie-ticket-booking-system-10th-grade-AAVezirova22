cmake_minimum_required(VERSION 3.31)
project(BookingSystem)

set(CMAKE_CXX_STANDARD 14)


add_executable(BookingSystem
        src/app.cpp
        src/login.cpp
        src/main.cpp
        src/mainMenu.cpp
        src/register.cpp

        include/app.h
        include/login.h
        include/mainMenu.h
        include/register.h)



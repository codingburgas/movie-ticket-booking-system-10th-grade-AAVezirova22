cmake_minimum_required(VERSION 3.31)
project(BookingSystem)

set(CMAKE_CXX_STANDARD 14)

include_directories(businessLogicLayer)
include_directories(dataAccessLayer)

add_executable(BookingSystem
    businessLogicLayer/app.cpp
    businessLogicLayer/app.h
    dataAccessLayer/dataHandler.cpp
    dataAccessLayer/dataHandler.h
    presentationLayer/menu.cpp
    presentationLayer/menu.h
        src/main.cpp)

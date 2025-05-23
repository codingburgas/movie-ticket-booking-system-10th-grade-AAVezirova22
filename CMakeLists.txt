cmake_minimum_required(VERSION 3.20)
project(BookingSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/opt/mysql-connector-c++")
find_package(mysql-concpp CONFIG REQUIRED)

list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/opt/openssl@3")
find_package(OpenSSL REQUIRED)

add_executable(BookingSystem
        src/app.cpp
        src/login.cpp
        src/main.cpp
        src/mainMenu.cpp
        src/register.cpp
        src/db.cpp

        include/app.h
        include/login.h
        include/mainMenu.h
        include/register.h
        include/db.h
        include/user.h
)

target_link_directories(BookingSystem PRIVATE /opt/homebrew/opt/openssl@3/lib)

target_link_libraries(BookingSystem
        PRIVATE
        mysql::concpp
        OpenSSL::SSL
        OpenSSL::Crypto
)
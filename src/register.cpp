#include <iostream>
#include <limits>
#include "../include/db.h"
#include "../include/register.h"

bool registerUser()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string username, email, password;

    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    std::cout << "Enter email   : ";
    std::getline(std::cin, email);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    try {
        if (registerNewUser(username, email, password)) {
            std::cout << "User registered successfully.\n";
            return true;
        } else {
            std::cout << "Nothing inserted – check your data.\n";
            return false;
        }
    }
    catch (const mysqlx::Error& e) {
        std::cerr << "Registration failed: " << e.what() << '\n';
        return false;
    }
}
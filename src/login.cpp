#include <iostream>
#include <limits>
#include "../include/db.h"
#include "../include/login.h"

std::optional<User> loginUser()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string username, password;

    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    try {
        auto user = tryLogin(username, password);

        if (user) {
            std::cout << "Login successful. Welcome, "
                      << user->username << "!\n";
        } else {
            std::cout << "Invalid username or password.\n";
        }

        return user;
    }
    catch (const mysqlx::Error& e) {
        std::cerr << "Login failed: " << e.what() << '\n';
        return std::nullopt;
    }
}
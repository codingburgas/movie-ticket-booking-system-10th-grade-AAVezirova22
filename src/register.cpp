#include <iostream>
#include <limits>
#include "../include/db.h"

void registerUser()
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
        auto session = createSession();
        auto schema  = session->getSchema("TicketBookingSystem");
        auto users   = schema.getTable("users");

        auto res = users
            .insert("username", "email", "password")
            .values(username, email, password)
            .execute();

        if (res.getAffectedItemsCount() == 1)
            std::cout << "User registered successfully.\n";
        else
            std::cout << "Nothing inserted – check your data.\n";
    }
    catch (const mysqlx::Error& e) {
        std::cerr << "Registration failed: " << e.what() << '\n';
    }
}
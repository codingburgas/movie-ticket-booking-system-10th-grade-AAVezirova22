#include <iostream>
#include <limits>
#include "../include/db.h"

void loginUser()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string username, password;

    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    try {
        auto session = createSession();
        auto schema  = session->getSchema("TicketBookingSystem");
        auto users   = schema.getTable("users");

        auto res = users
            .select("username")
            .where("username = :u AND password = :p")
            .bind("u", username)
            .bind("p", password)
            .execute();

        if (res.count() > 0)
            std::cout << "Login successful. Welcome, " << username << "!\n";
        else
            std::cout << "Invalid username or password.\n";
    }
    catch (const mysqlx::Error& e) {
        std::cerr << "Login failed: " << e.what() << '\n';
    }
}
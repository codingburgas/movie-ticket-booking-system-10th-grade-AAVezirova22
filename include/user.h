#ifndef USER_H
#define USER_H

#include <string>

struct User {
    int id;
    std::string username;
    std::string email;
    std::string role;

    bool isAdmin() const { return role == "admin"; }
};

#endif

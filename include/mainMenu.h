#ifndef MENU_H
#define MENU_H

#include <string>
#include "user.h"

class Menu {
public:
    void displayMainMenu();

    void displayLogin();
    void displayRegister();

    void drawTeamName();
    void drawRegister();
    void drawMainMenu();
    void drawUserMenu();

private:
    void displayUserMenu (const User& currentUser);
    void displayAdminMenu(const User& currentUser);

    static void clearScreen();

    void promoteUser();
    void demoteUser();

    int  choice = 0;
    bool hasUpper = false;
    bool hasDigit = false;
    bool hasSpecialChar = false;
    bool passLength = false;

    std::string username;
    std::string password;

    User loggedUser{};
};

#endif
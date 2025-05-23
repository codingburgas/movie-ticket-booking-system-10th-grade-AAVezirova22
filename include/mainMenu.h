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
    void drawAdminMenu();

private:
    void displayUserMenu (const User& currentUser);
    void displayAdminMenu(const User& currentUser);

    static void clearScreen();

    void promoteUser();
    void demoteUser();

    void addCinemaMenu();
    void addHallMenu();
    void addMovieMenu();
    void listCinemasMenu();
    void listMoviesMenu();

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
#ifndef MENU_H
#define MENU_H

#include <string>
#include "user.h"

class Menu
{
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
    void displayUserMenu(const User& currentUser);
    void displayAdminMenu(const User& currentUser);

    static void clearScreen();

    void promoteUser();
    void demoteUser();

    void addCinemaMenu();
    void addHallMenu();
    void addMovieMenu();
    void addShowtimeMenu();

    void listCinemasMenu();
    void listMoviesMenu();
    void listShowtimesMenu();

    void viewMoviesMenu();

    void editCinemaMenu();
    void editHallMenu();
    void editMovieMenu();
    void editShowtimeMenu();

    void deleteCinemaMenu();
    void deleteHallMenu();
    void deleteMovieMenu();
    void deleteShowtimeMenu();

    int         choice      = 0;
    std::string username;
    std::string password;
    User        loggedUser{};
};

#endif
#ifndef MENU_H
#define MENU_H

#include <string>

class Menu {
public:
    void displayMainMenu();
    void displayLogin();
    //void viewMovies();
    void drawTeamName();
    void drawRegister();
    void displayRegister();
    void displayUserMenu();


    //void emailValidation();
    //void passwordValidation();
    //void passwordMatch();
    //void usernameValidation();

private:
    int choice;

    std::string email = "";
    std::string username = "";
    std::string password = "";
    std::string confirmPassword = "";

    bool hasUpper = false;
    bool hasDigit = false;
    bool hasSpecialChar = false;
    bool passLength = false;
};



#endif

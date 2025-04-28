#include "../include/mainMenu.h"
#include <iostream>
#include <iomanip>
#include <fstream>

static void clearScreen() {
#ifdef _WIN64
    system("cls");
#elif __APPLE__
    system("clear");
#endif
}

void Menu::displayMainMenu() {
    drawTeamName();
    std::cout << std::setw(97) << "==========================================================================\n";
    std::cout << std::setw(97) << "|                                MAIN MENU                               |\n";
    std::cout << std::setw(97) << "==========================================================================\n";
    std::cout << std::setw(97) << "|                                                                        |\n";
    std::cout << std::setw(97) << "|                                1. Login                                |\n";
    std::cout << std::setw(97) << "|                                1. Register                             |\n";
    std::cout << std::setw(97) << "|                                2. View all movies                      |\n";
    std::cout << std::setw(97) << "|                                3. Exit                                 |\n";
    std::cout << std::setw(97) << "|                                                                        |\n";
    std::cout << std::setw(97) << "==========================================================================\n";
    std::cout << std::setw(60) << "Enter your choice: ";

    std::cin >> choice;

    switch (choice) {
        case 1: displayLogin(); break;
        case 2: displayRegister(); break;
        //tuk trqbva da ima viewMovies(); break;
        case 3:break;
        case 4: break;
        default:
            std::cout << "Invalid input. Please try again!\n";
        return;
    }
}

void Menu::displayUserMenu() {
    drawTeamName();
    std::cout << std::setw(97) << "==========================================================================\n";
    std::cout << std::setw(97) << "|                                MAIN MENU                               |\n";
    std::cout << std::setw(97) << "==========================================================================\n";
    std::cout << std::setw(97) << "|                                                                        |\n";
    std::cout << std::setw(97) << "|                                2. View all movies                      |\n";
    std::cout << std::setw(97) << "|                                3. Exit                                 |\n";
    std::cout << std::setw(97) << "|                                                                        |\n";
    std::cout << std::setw(97) << "==========================================================================\n";
    std::cout << std::setw(60) << "Enter your choice: ";

    std::cin >> choice;

    switch (choice) {
        //tuk trqbva da ima viewMovies(); break;
        case 1: system("clear");
        case 2: break;
        default:
            std::cout << "Invalid input. Please try again!\n";
        return;
    }
}


void Menu::drawTeamName() {
        std::ifstream file("../assets/drawTeamName.txt");

        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }

        file.close();
}

void Menu::displayLogin() {
    clearScreen();
    std::cout << '\n';
    drawTeamName();

    std::cout << std::setw(97) << "==========================================================================\n";
    std::cout << std::setw(97) << "|                                LOGIN                                   |\n";
    std::cout << std::setw(97) << "==========================================================================\n";
    std::cout << std::setw(97) << "|                                                                        |\n";
    std::cout << std::setw(67) << "                        Enter your username: ";
    std::cin >> username;

    std::cout << std::setw(97) << "|                                                                        |\n";
    std::cout << std::setw(67) << "                        Enter your password: ";
    std::cin >> password;
    std::cout << std::setw(97) << "|                                                                        |\n";

    // if (!LoginManager::login(username, password)) {
    //     displayLogin();
    // }
    // else {
    //     displayUserMenu();
    // }

    std::cout << std::setw(97) << "|                                                                        |\n";
    std::cout << std::setw(97) << "==========================================================================\n";
}

//Displays the register menu
void Menu::drawRegister() {
    clearScreen();
    std::cout << '\n';
    drawTeamName();

    std::cout << std::setw(97) << "==========================================================================\n";
    std::cout << std::setw(97) << "|                                REGISTER                                |\n";
    std::cout << std::setw(97) << "==========================================================================\n";
    std::cout << std::setw(97) << "|                                                                        |\n";
    //emailValidation();

    std::cout << std::setw(97) << "|                                                                        |\n";
    //usernameValidation();

    std::cout << std::setw(97) << "|                                                                        |\n";
    //passwordValidation();

    std::cout << std::setw(97) << "|                                                                        |\n";
    //passwordMatch();

    std::cout << std::setw(97) << "|                                                                        |\n";
    std::cout << std::setw(97) << "==========================================================================\n";
}

void Menu::displayRegister() {
    drawRegister();

    // if (RegisterManager::registerUser(username, password)) {
    //     std::cout << "User registered successfully!\n";
    //     displayLogin();
    // }
    // else {
    //     std::cout << "Registration failed!\n";
    // }
}
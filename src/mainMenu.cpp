#include "../include/mainMenu.h"
#include "../include/login.h"
#include "../include/register.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>

void clearScreen()
{
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

void Menu::displayMainMenu()
{
    while (true) {
        clearScreen();
        drawTeamName();

        std::cout << std::setw(97) << "==========================================================================\n";
        std::cout << std::setw(97) << "|                                MAIN MENU                               |\n";
        std::cout << std::setw(97) << "==========================================================================\n";
        std::cout << std::setw(97) << "|                                                                        |\n";
        std::cout << std::setw(97) << "|                                1. Login                                |\n";
        std::cout << std::setw(97) << "|                                2. Register                             |\n";
        std::cout << std::setw(97) << "|                                3. View all movies (TODO)               |\n";
        std::cout << std::setw(97) << "|                                4. Exit                                 |\n";
        std::cout << std::setw(97) << "|                                                                        |\n";
        std::cout << std::setw(97) << "==========================================================================\n";
        std::cout << std::setw(60) << "Enter your choice: ";

        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                loginUser();
                break;
            case 2:
                registerUser();
                break;
            case 3:
                std::cout << "\n[viewMovies() not implemented yet]\n";
                break;
            case 4:
                std::cout << "\nExiting… Bye!\n";
                return;
            default:
                std::cout << "\nInvalid input. Please try again!\n";
                break;
        }

        std::cout << "\nPress <Enter> to continue…";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
}

void Menu::displayUserMenu()
{
    clearScreen();
    drawTeamName();

    std::cout << std::setw(97) << "==========================================================================\n";
    std::cout << std::setw(97) << "|                               USER  MENU                               |\n";
    std::cout << std::setw(97) << "==========================================================================\n";
    std::cout << std::setw(97) << "|                                                                        |\n";
    std::cout << std::setw(97) << "|                                1. View all movies (TODO)               |\n";
    std::cout << std::setw(97) << "|                                2. Logout                               |\n";
    std::cout << std::setw(97) << "|                                                                        |\n";
    std::cout << std::setw(97) << "==========================================================================\n";
    std::cout << std::setw(60) << "Enter your choice: ";

    std::cin >> choice;

    switch (choice) {
        case 1:
            std::cout << "\n[viewMovies() not implemented yet]\n";
            break;
        case 2:
            std::cout << "\nLogging out…\n";
            return;
        default:
            std::cout << "Invalid input. Please try again!\n";
            break;
    }

    std::cout << "\nPress <Enter> to continue…";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void Menu::drawTeamName()
{
    std::ifstream file("../assets/drawTeamName.txt");
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line))
        std::cout << line << '\n';
}

void Menu::drawRegister()
{
    clearScreen();
    drawTeamName();

    std::cout << std::setw(97) << "==========================================================================\n";
    std::cout << std::setw(97) << "|                                REGISTER                                |\n";
    std::cout << std::setw(97) << "==========================================================================\n";
    std::cout << std::setw(97) << "|                                                                        |\n";
    std::cout << std::setw(97) << "|                 (validation prompts moved to RegisterUser)             |\n";
    std::cout << std::setw(97) << "|                                                                        |\n";
    std::cout << std::setw(97) << "==========================================================================\n";
}

void Menu::displayLogin()  {}
void Menu::displayRegister(){}
#include "../include/mainMenu.h"
#include "../include/login.h"
#include "../include/register.h"
#include "../include/db.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include <vector>

void Menu::clearScreen()
{
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

void Menu::drawTeamName()
{
    std::ifstream file("../assets/drawTeamName.txt");
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line))
        std::cout << line << '\n';
}

void Menu::drawMainMenu() {
    std::ifstream file("../assets/drawMainMenu.txt");
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line))
        std::cout << line << '\n';
}

void Menu::drawUserMenu() {
    std::ifstream file("../assets/drawUserMenu.txt");
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line))
        std::cout << line << '\n';
}

void Menu::drawAdminMenu() {
    std::ifstream file("../assets/drawAdminMenu.txt");
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line))
        std::cout << line << '\n';
}


void Menu::displayMainMenu()
{
    while (true) {
        clearScreen();
        drawTeamName();
        drawMainMenu();

        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                auto user = loginUser();
                if (user) {
                    if (user->isAdmin())
                        displayAdminMenu(*user);
                    else
                        displayUserMenu (*user);
                }
                break;
            }
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

void Menu::displayUserMenu(const User&)
{
    clearScreen();
    drawTeamName();
    drawUserMenu();

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
}


void Menu::displayAdminMenu(const User& currentUser)
{
    loggedUser = currentUser;

    while (true) {
        clearScreen();
        drawTeamName();
        drawAdminMenu();

        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: promoteUser(); break;
            case 2: demoteUser (); break;
            case 3:
                std::cout << "\n[addCinemaOrMovie() not implemented yet]\n";
                break;
            case 4:
                std::cout << "\nLogging out…\n";
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


void Menu::promoteUser()
{
    auto users = fetchAllUsers();

    std::cout << "\nCurrent users:\n";
    std::cout << "ID  Username        Role\n";
    std::cout << "---------------------------------\n";
    for (const auto& u : users)
        std::cout << std::left << std::setw(4)  << u.id
                  << std::setw(16) << u.username
                  << u.role << '\n';

    int id;
    std::cout << "\nEnter user ID to promote: ";
    std::cin  >> id;

    if (changeUserRole(id, "admin"))
        std::cout << "Promotion successful.\n";
    else
        std::cout << "Promotion failed.\n";
}

void Menu::demoteUser()
{
    auto users = fetchAllUsers();

    std::cout << "\nCurrent admins:\n";
    std::cout << "ID  Username\n";
    std::cout << "----------------------\n";
    for (const auto& u : users)
        if (u.isAdmin())
            std::cout << std::left << std::setw(4) << u.id
                      << u.username << '\n';

    int id;
    std::cout << "\nEnter admin ID to demote: ";
    std::cin  >> id;

    if (id == loggedUser.id) {
        std::cout << "You cannot demote yourself while logged in.\n";
        return;
    }

    if (changeUserRole(id, "user"))
        std::cout << "Demotion successful.\n";
    else
        std::cout << "Demotion failed.\n";
}
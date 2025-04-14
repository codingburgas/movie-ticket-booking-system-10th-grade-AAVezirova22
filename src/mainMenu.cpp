#include "../include/mainMenu.h"
#include <iostream>
#include <iomanip>

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
        case 1: break;
        case 2: break;
        default:
            std::cout << "Invalid input. Please try again!\n";
        return;
    }
}


void Menu::drawTeamName() {
    std::cout << "  __  __            _        _   _      _        _     _                 _    _                             _                 " << std::endl;
    std::cout << " |  \\/  |          (_)      | | (_)    | |      | |   | |               | |  (_)                           | |                " << std::endl;
    std::cout << " | \\  / | _____   ___  ___  | |_ _  ___| | _____| |_  | |__   ___   ___ | | ___ _ __   __ _   ___ _   _ ___| |_ ___ _ __ ___  " << std::endl;
    std::cout << " | |\\/| |/ _ \\ \\ / / |/ _ \\ | __| |/ __| |/ / _ \\ __| | '_ \\ / _ \\ / _ \\| |/ / | '_ \\ / _` | / __| | | / __| __/ _ \\ '_ ` _ \\ " << std::endl;
    std::cout << " | |  | | (_) \\ V /| |  __/ | |_| | (__|   <  __/ |_  | |_) | (_) | (_) |   <| | | | | (_| | \\__ \\ |_| \\__ \\ ||  __/ | | | | |" << std::endl;
    std::cout << " |_|  |_|\\___/ \\_/ |_|\\___|  \\__|_|\\___|_|\\_\\___|\\__| |_.__/ \\___/ \\___/|_|\\_\\_|_| |_|\\__, | |___/\\__, |___/\\__\\___|_| |_| |_|" << std::endl;
    std::cout << "                                                                                       __/ |       __/ |                      " << std::endl;
    std::cout << "                                                                                      |___/       |___/                       " << std::endl;
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
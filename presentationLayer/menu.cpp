//
// Created by Ani Vezirova on 10.03.25.
//
#include "menu.h"
#include <iostream>


void Menu::displayMainMenu() {
    int choice;
    while (true) {
        std::cout << "  __  __            _        _   _      _        _     _                 _    _                             _                 " << std::endl;
        std::cout << " |  \\/  |          (_)      | | (_)    | |      | |   | |               | |  (_)                           | |                " << std::endl;
        std::cout << " | \\  / | _____   ___  ___  | |_ _  ___| | _____| |_  | |__   ___   ___ | | ___ _ __   __ _   ___ _   _ ___| |_ ___ _ __ ___  " << std::endl;
        std::cout << " | |\\/| |/ _ \\ \\ / / |/ _ \\ | __| |/ __| |/ / _ \\ __| | '_ \\ / _ \\ / _ \\| |/ / | '_ \\ / _` | / __| | | / __| __/ _ \\ '_ ` _ \\ " << std::endl;
        std::cout << " | |  | | (_) \\ V /| |  __/ | |_| | (__|   <  __/ |_  | |_) | (_) | (_) |   <| | | | | (_| | \\__ \\ |_| \\__ \\ ||  __/ | | | | |" << std::endl;
        std::cout << " |_|  |_|\\___/ \\_/ |_|\\___|  \\__|_|\\___|_|\\_\\___|\\__| |_.__/ \\___/ \\___/|_|\\_\\_|_| |_|\\__, | |___/\\__, |___/\\__\\___|_| |_| |_|" << std::endl;
        std::cout << "                                                                                       __/ |       __/ |                      " << std::endl;
        std::cout << "                                                                                      |___/       |___/                       " << std::endl;

        std::cout << "1. Login" << std::endl;
        std::cout << "2. View all movies" << std::endl;
        std::cout << "3. Exit" << std::endl;

        std::cin >> choice;

        switch (choice) {
            case 1:
                login();
            break;
            case 2:
                viewMovies();
            break;
            case 3:
                return;
            default:
                std::cout << "Invalid choice, please try again." << std::endl;
        }
    }
}

void Menu::login() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    std::cout << "Login successful!\n";
}

void Menu::viewMovies() {
    std::cout << "Displaying all movies...\n";
}

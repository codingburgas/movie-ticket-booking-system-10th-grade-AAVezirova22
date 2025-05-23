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
                std::cout << std::endl << "[viewMovies() not implemented yet]" << std::endl;
                break;
            case 4:
                std::cout << std::endl << "Exiting… Bye!" << std::endl;
                return;
            default:
                std::cout << std::endl << "Invalid input. Please try again!" << std::endl;
                break;
        }

        std::cout << std::endl << "Press <Enter> to continue…";
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
            std::cout << std::endl << "[viewMovies() not implemented yet]" << std::endl;
            break;
        case 2:
            std::cout << std::endl << "Logging out..." << std::endl;
            return;
        default:
            std::cout << "Invalid input. Please try again!" << std::endl;
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
            case 1: promoteUser();      break;
            case 2: demoteUser();       break;
            case 3: addCinemaMenu();    break;
            case 4: addHallMenu();      break;
            case 5: addMovieMenu();     break;
            case 6: listCinemasMenu();  break;
            case 7: listMoviesMenu();   break;
            case 8: std::cout << std::endl <<  "Logging out…" << std::endl;; return;
            default: std::cout << std::endl << "Invalid input. Please try again!" << std::endl;; break;
        }

        std::cout << std::endl << "Press <Enter> to continue…";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
}


void Menu::promoteUser()
{
    auto users = fetchAllUsers();

    std::cout << std::endl << "Current users:" << std::endl;
    std::cout << "ID  Username        Role\n";
    std::cout << "---------------------------------" << std::endl;
    for (const auto& u : users)
        std::cout << std::left << std::setw(4)  << u.id
                  << std::setw(16) << u.username
                  << u.role << '\n';

    int id;
    std::cout << std::endl << "Enter user ID to promote: ";
    std::cin  >> id;

    if (changeUserRole(id, "admin"))
        std::cout << "Promotion successful." << std::endl;
    else
        std::cout << "Promotion failed." << std::endl;
}

void Menu::demoteUser()
{
    auto users = fetchAllUsers();

    std::cout << std::endl << "Current admins:" << std::endl;
    std::cout << "ID  Username" << std::endl;
    std::cout << "----------------------" << std::endl;
    for (const auto& u : users)
        if (u.isAdmin())
            std::cout << std::left << std::setw(4) << u.id
                      << u.username << '\n';

    int id;
    std::cout << std::endl << "Enter admin ID to demote: ";
    std::cin  >> id;

    if (id == loggedUser.id) {
        std::cout << "You cannot demote yourself while logged in." << std::endl;
        return;
    }

    if (changeUserRole(id, "user"))
        std::cout << "Demotion successful." << std::endl;
    else
        std::cout << "Demotion failed." << std::endl;
}

void Menu::addCinemaMenu()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string name, city;

    std::cout << std::endl << "Cinema name: "; std::getline(std::cin, name);
    std::cout << "City: "; std::getline(std::cin, city);

    if (addCinema(name, city))
        std::cout << "Cinema added" << std::endl;
    else
        std::cout << "Failed to add cinema" << std::endl;
}

void Menu::addHallMenu()
{
    int cinemaId, seats, rows;
    std::string hallName;

    auto cinemas = fetchAllCinemas();
    if (cinemas.empty()) { std::cout << "No cinemas yet." << std::endl; return; }

    std::cout << std::endl << "Current cinemas:" << std::endl;
    for (auto& c : cinemas)
        std::cout << c.id << " — " << c.name << " (" << c.city << ")\n";

    std::cout << "Cinema ID to attach hall to: "; std::cin >> cinemaId;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Hall name: "; std::getline(std::cin, hallName);
    std::cout << "Seats per row: "; std::cin >> seats;
    std::cout << "Row count: "; std::cin >> rows;

    if (addHall(cinemaId, hallName, seats, rows))
        std::cout << "Hall added." << std::endl;
    else
        std::cout << "Failed to add hall." << std::endl;
}

void Menu::addMovieMenu()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string title, language, genre, date;
    int duration;

    std::cout << std::endl << "Title: "; std::getline(std::cin, title);
    std::cout << "Language: "; std::getline(std::cin, language);
    std::cout << "Genre: "; std::getline(std::cin, genre);
    std::cout << "Release date (YYYY-MM-DD): "; std::getline(std::cin, date);
    std::cout << "Duration (min): "; std::cin  >> duration;

    if (addMovie(title, language, genre, date, duration))
        std::cout << "Movie added." << std::endl;
    else
        std::cout << "Failed to add movie." << std::endl;
}

void Menu::listCinemasMenu()
{
    auto cinemas = fetchAllCinemas();
    if (cinemas.empty()) { std::cout << "No cinemas." << std::endl; return; }

    std::cout << std::endl << "ID  Name (City)\n---------------------------" << std::endl;
    for (auto& c : cinemas)
        std::cout << c.id << "  " << c.name << " (" << c.city << ")" << std::endl;
}


void Menu::listMoviesMenu()
{
    auto movies = fetchAllMovies();
    if (movies.empty()) { std::cout << "No movies." << std::endl; return; }

    std::cout << std::endl << "ID  Title — Genre — Language — Release" << std::endl;
    std::cout << "----------------------------------------------" << std::endl;
    for (auto& m : movies)
        std::cout << m.id << "  " << m.title << " — "
                  << m.genre << " — " << m.language
                  << " — " << m.releaseDate << '\n';
}
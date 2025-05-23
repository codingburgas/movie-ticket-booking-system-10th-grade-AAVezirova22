#ifndef DB_H
#define DB_H

#include <mysqlx/xdevapi.h>
#include <optional>
#include <vector>
#include "user.h"

std::shared_ptr<mysqlx::Session> createSession();

std::optional<User> tryLogin   (const std::string& username, const std::string& password);

bool registerNewUser(const std::string& username, const std::string& email, const std::string& password);

bool changeUserRole (int userId, const std::string& newRole);

std::vector<User>   fetchAllUsers();

struct Cinema { int id; std::string name; std::string city; };
struct Hall   { int id, cinemaId, seatsPerRow, rowCount; std::string name; };
struct Movie  { int id; std::string title, language, genre, releaseDate; };

bool addCinema (const std::string& name, const std::string& city);
bool deleteCinema (int cinemaId);
std::vector<Cinema> fetchAllCinemas();

bool addHall (int cinemaId, const std::string& name,
              int seatsPerRow, int rowCount);
bool deleteHall(int hallId);
std::vector<Hall> fetchHallsByCinema(int cinemaId);

bool addMovie (const std::string& title, const std::string& language, const std::string& genre, const std::string& releaseDate, int durationMin);
bool deleteMovie(int movieId);
std::vector<Movie> fetchAllMovies();

#endif
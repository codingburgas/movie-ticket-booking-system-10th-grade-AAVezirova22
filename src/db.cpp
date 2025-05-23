#include "../include/db.h"
#include <stdexcept>
#include <iostream>

namespace {
    std::shared_ptr<mysqlx::Session> make_shared(mysqlx::Session* sess) {
        return std::shared_ptr<mysqlx::Session>(sess,
            [](mysqlx::Session* p){ try { delete p; } catch(...) {} });
    }
}

std::shared_ptr<mysqlx::Session> createSession()
{
    auto *sess = new mysqlx::Session("127.0.0.1", 33060, "root", "admin");
    sess->sql("USE TicketBookingSystem").execute();
    return make_shared(sess);
}


std::optional<User> tryLogin(const std::string& username,
                             const std::string& password)
{
    auto session = createSession();
    auto users   = session->getSchema("TicketBookingSystem").getTable("users");

    auto res = users
        .select("id", "username", "email", "role")
        .where("username = :u AND password = :p")
        .bind("u", username)
        .bind("p", password)
        .execute();

    if (res.count() == 0) return std::nullopt;

    auto row = res.fetchOne();

    return User{
        row[0].get<int>(),
        row[1].get<std::string>(),
        row[2].get<std::string>(),
        row[3].get<std::string>()
    };
}

bool registerNewUser(const std::string& username,
                     const std::string& email,
                     const std::string& password)
{
    auto session = createSession();
    auto users   = session->getSchema("TicketBookingSystem").getTable("users");

    auto res = users
        .insert("username", "email", "password", "role")
        .values(username, email, password, "user")
        .execute();

    return res.getAffectedItemsCount() == 1;
}

bool changeUserRole(int userId, const std::string& newRole)
{
    if (newRole != "user" && newRole != "admin") return false;

    auto session = createSession();
    auto users   = session->getSchema("TicketBookingSystem").getTable("users");

    auto res = users
        .update()
        .set("role", newRole)
        .where("id = :id")
        .bind("id", userId)
        .execute();

    return res.getAffectedItemsCount() == 1;
}

std::vector<User> fetchAllUsers()
{
    std::vector<User> list;

    auto session = createSession();
    auto users   = session->getSchema("TicketBookingSystem").getTable("users");

    auto res = users.select("id", "username", "email", "role").execute();
    for (mysqlx::Row row : res)
        list.push_back( User{
            row[0].get<int>(),
            row[1].get<std::string>(),
            row[2].get<std::string>(),
            row[3].get<std::string>()
        });

    return list;
}

bool addCinema(const std::string& name, const std::string& city)
{
    auto s = createSession();
    auto t = s->getSchema("TicketBookingSystem").getTable("cinema");

    return t.insert("name","city")
            .values(name, city)
            .execute()
            .getAffectedItemsCount() == 1;
}

bool deleteCinema(int id)
{
    auto s = createSession();
    auto t = s->getSchema("TicketBookingSystem").getTable("cinema");

    return t.remove()
            .where("id = :id")
            .bind("id", id)
            .execute()
            .getAffectedItemsCount() == 1;
}

std::vector<Cinema> fetchAllCinemas()
{
    std::vector<Cinema> list;
    auto s = createSession();
    auto res = s->getSchema("TicketBookingSystem")
                .getTable("cinema")
                .select("id","name","city")
                .execute();

    for (mysqlx::Row r : res)
        list.push_back({ r[0].get<int>(), r[1].get<std::string>(),
                         r[2].get<std::string>() });
    return list;
}

bool addHall(int cinemaId, const std::string& name,
             int seatsPerRow, int rowCount)
{
    auto s = createSession();
    auto t = s->getSchema("TicketBookingSystem").getTable("hall");

    return t.insert("cinema_id","name","seats_per_row","row_count")
            .values(cinemaId, name, seatsPerRow, rowCount)
            .execute()
            .getAffectedItemsCount() == 1;
}

bool deleteHall(int hallId)
{
    auto s = createSession();
    auto t = s->getSchema("TicketBookingSystem").getTable("hall");

    return t.remove().where("id = :id")
            .bind("id", hallId)
            .execute()
            .getAffectedItemsCount() == 1;
}

std::vector<Hall> fetchHallsByCinema(int cinemaId)
{
    std::vector<Hall> list;
    auto s = createSession();
    auto res = s->getSchema("TicketBookingSystem")
                .getTable("hall")
                .select("id","cinema_id","name","seats_per_row","row_count")
                .where("cinema_id = :cid")
                .bind("cid", cinemaId)
                .execute();

    for (mysqlx::Row r : res)
        list.push_back({ r[0].get<int>(),  r[1].get<int>(),
                         r[3].get<int>(),  r[4].get<int>(),
                         r[2].get<std::string>() });
    return list;
}

bool addMovie(const std::string& title, const std::string& language,
              const std::string& genre, const std::string& releaseDate,
              int durationMin)
{
    auto s = createSession();
    auto t = s->getSchema("TicketBookingSystem").getTable("movie");

    return t.insert("title","language","genre","release_date","duration_min")
            .values(title, language, genre, releaseDate, durationMin)
            .execute()
            .getAffectedItemsCount() == 1;
}

bool deleteMovie(int movieId)
{
    auto s = createSession();
    auto t = s->getSchema("TicketBookingSystem").getTable("movie");

    return t.remove().where("id = :id")
            .bind("id", movieId)
            .execute()
            .getAffectedItemsCount() == 1;
}

std::vector<Movie> fetchAllMovies()
{
    std::vector<Movie> list;
    auto s = createSession();
    auto res = s->getSchema("TicketBookingSystem")
                .getTable("movie")
                .select("id","title","language","genre",
                        "DATE_FORMAT(release_date,'%Y-%m-%d')")
                .execute();

    for (mysqlx::Row r : res)
        list.push_back({ r[0].get<int>(),  r[1].get<std::string>(),
                         r[2].get<std::string>(), r[3].get<std::string>(),
                         r[4].get<std::string>() });
    return list;
}
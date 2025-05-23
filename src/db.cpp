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
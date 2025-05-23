#ifndef DB_H
#define DB_H

#include <mysqlx/xdevapi.h>
#include <memory>
#include <optional>
#include <vector>
#include "user.h"

std::shared_ptr<mysqlx::Session> createSession();

std::optional<User> tryLogin   (const std::string& username, const std::string& password);

bool registerNewUser(const std::string& username, const std::string& email, const std::string& password);

bool changeUserRole (int userId, const std::string& newRole);

std::vector<User>   fetchAllUsers();

#endif
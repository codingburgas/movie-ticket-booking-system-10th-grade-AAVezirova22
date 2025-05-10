#ifndef DB_H
#define DB_H

#include <mysqlx/xdevapi.h>
#include <memory>

std::shared_ptr<mysqlx::Session> createSession();

#endif
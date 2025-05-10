#include "../include/db.h"

namespace {
    std::shared_ptr<mysqlx::Session> make_shared(mysqlx::Session* sess) {
        return std::shared_ptr<mysqlx::Session>(sess,
            [](mysqlx::Session* p){ try { delete p; } catch(...) {} });
    }
}

std::shared_ptr<mysqlx::Session> createSession()
{
    try {
        auto *sess = new mysqlx::Session("127.0.0.1", 33060, "root", "admin");
        sess->sql("USE TicketBookingSystem").execute();
        return make_shared(sess);
    }
    catch (const mysqlx::Error& e) {
        throw;
    }
}
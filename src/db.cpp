#include "../include/db.h"
#include <iostream>
#include <fstream>

namespace {
    std::shared_ptr<mysqlx::Session> make_shared(mysqlx::Session *sess) {
        return std::shared_ptr<mysqlx::Session>(sess,
                                                [](mysqlx::Session *p) {
                                                    try { delete p; } catch (...) {
                                                    }
                                                });
    }
}

std::shared_ptr<mysqlx::Session> createSession() {
    auto *sess = new mysqlx::Session("127.0.0.1", 33060, "root", "admin");
    sess->sql("USE TicketBookingSystem").execute();
    return make_shared(sess);
}

std::optional<User> tryLogin(const std::string &username, const std::string &password) {
    auto session = createSession();
    auto table = session->getSchema("TicketBookingSystem").getTable("users");

    auto res = table.select("id", "username", "email", "role")
            .where("username = :u AND password = :p")
            .bind("u", username)
            .bind("p", password)
            .execute();

    if (res.count() == 0) {
        return std::nullopt;
    }

    mysqlx::Row row = res.fetchOne();

    return User{
        row[0].get<int>(),
        row[1].get<std::string>(),
        row[2].get<std::string>(),
        row[3].get<std::string>()
    };
}

bool registerNewUser(const std::string &username, const std::string &email, const std::string &password) {
    auto session = createSession();
    auto table = session->getSchema("TicketBookingSystem").getTable("users");

    auto res = table.insert("username", "email", "password", "role")
            .values(username, email, password, "user")
            .execute();

    return res.getAffectedItemsCount() == 1;
}

bool changeUserRole(int userId, const std::string &newRole) {
    if (newRole != "user" && newRole != "admin") {
        return false;
    }

    auto session = createSession();
    auto table = session->getSchema("TicketBookingSystem").getTable("users");

    auto res = table.update()
            .set("role", newRole)
            .where("id = :i")
            .bind("i", userId)
            .execute();

    return res.getAffectedItemsCount() == 1;
}

std::vector<User> fetchAllUsers() {
    std::vector<User> list;

    auto session = createSession();
    auto table = session->getSchema("TicketBookingSystem").getTable("users");

    auto res = table.select("id", "username", "email", "role").execute();

    for (mysqlx::Row r: res) {
        list.push_back(
            {
                r[0].get<int>(),
                r[1].get<std::string>(),
                r[2].get<std::string>(),
                r[3].get<std::string>()
            });
    }

    return list;
}

bool addCinema(const std::string &name, const std::string &city) {
    auto session = createSession();
    auto table = session->getSchema("TicketBookingSystem").getTable("cinema");

    auto res = table.insert("name", "city")
            .values(name, city)
            .execute();

    return res.getAffectedItemsCount() == 1;
}

bool deleteCinema(int id) {
    auto session = createSession();
    auto table = session->getSchema("TicketBookingSystem").getTable("cinema");

    auto res = table.remove()
            .where("id = :i")
            .bind("i", id)
            .execute();

    return res.getAffectedItemsCount() == 1;
}

std::vector<Cinema> fetchAllCinemas() {
    std::vector<Cinema> list;

    auto session = createSession();
    auto res = session->getSchema("TicketBookingSystem")
            .getTable("cinema")
            .select("id", "name", "city")
            .execute();

    for (mysqlx::Row r: res) {
        list.push_back(
            {
                r[0].get<int>(),
                r[1].get<std::string>(),
                r[2].get<std::string>()
            });
    }

    return list;
}

bool addHall(int cinemaId, const std::string &name, int seatsPerRow, int rowCount) {
    auto session = createSession();
    auto table = session->getSchema("TicketBookingSystem").getTable("hall");

    auto res = table.insert("cinema_id", "name", "seats_per_row", "row_count")
            .values(cinemaId, name, seatsPerRow, rowCount)
            .execute();

    return res.getAffectedItemsCount() == 1;
}

bool deleteHall(int hallId) {
    auto session = createSession();
    auto table = session->getSchema("TicketBookingSystem").getTable("hall");

    auto res = table.remove()
            .where("id = :i")
            .bind("i", hallId)
            .execute();

    return res.getAffectedItemsCount() == 1;
}

std::vector<Hall> fetchHallsByCinema(int cinemaId) {
    std::vector<Hall> list;

    auto session = createSession();
    auto res = session->getSchema("TicketBookingSystem")
            .getTable("hall")
            .select("id",
                    "cinema_id",
                    "name",
                    "seats_per_row",
                    "row_count")
            .where("cinema_id = :c")
            .bind("c", cinemaId)
            .execute();

    for (mysqlx::Row r: res) {
        list.push_back(
            {
                r[0].get<int>(),
                r[1].get<int>(),
                r[2].get<std::string>(),
                r[3].get<int>(),
                r[4].get<int>()
            });
    }

    return list;
}

bool addMovie(const std::string &title, const std::string &language, const std::string &genre, const std::string &releaseDate, int durationMin) {
    auto session = createSession();
    auto table = session->getSchema("TicketBookingSystem").getTable("movie");

    auto res = table.insert("title",
                            "language",
                            "genre",
                            "release_date",
                            "duration_min")
            .values(title, language, genre, releaseDate, durationMin)
            .execute();

    return res.getAffectedItemsCount() == 1;
}

bool deleteMovie(int movieId) {
    auto session = createSession();
    auto table = session->getSchema("TicketBookingSystem").getTable("movie");

    auto res = table.remove()
            .where("id = :i")
            .bind("i", movieId)
            .execute();

    return res.getAffectedItemsCount() == 1;
}

std::vector<Movie> fetchAllMovies() {
    std::vector<Movie> list;

    auto session = createSession();
    auto res = session->getSchema("TicketBookingSystem")
            .getTable("movie")
            .select("id",
                    "title",
                    "language",
                    "genre",
                    "DATE_FORMAT(release_date,'%Y-%m-%d')")
            .execute();

    for (mysqlx::Row r: res) {
        list.push_back(
            {
                r[0].get<int>(),
                r[1].get<std::string>(),
                r[2].get<std::string>(),
                r[3].get<std::string>(),
                r[4].get<std::string>()
            });
    }

    return list;
}

bool addShowtime(int /*cinemaId*/, int hallId, int movieId, const std::string &startTime) {
    auto s = createSession();
    auto t = s->getSchema("TicketBookingSystem").getTable("showtime");


    auto res = t.insert("hall_id", "movie_id", "start_time")
            .values(hallId, movieId, startTime)
            .execute();
    return res.getAffectedItemsCount() == 1;
}

bool deleteShowtime(int showId) {
    auto session = createSession();
    auto table = session->getSchema("TicketBookingSystem").getTable("showtime");

    auto res = table.remove()
            .where("id = :i")
            .bind("i", showId)
            .execute();

    return res.getAffectedItemsCount() == 1;
}

std::vector<Showtime> fetchShowtimesByCinema(int cinemaId) {
    std::vector<Showtime> list;
    auto s = createSession();

    auto res = s->sql(
                "SELECT st.id, h.cinema_id, st.hall_id, st.movie_id, "
                "       DATE_FORMAT(st.start_time,'%Y-%m-%d %H:%i') AS dt "
                "FROM   showtime st "
                "JOIN   hall h ON h.id = st.hall_id "
                "WHERE  h.cinema_id = ? "
                "ORDER  BY st.start_time")
            .bind(cinemaId)
            .execute();

    for (mysqlx::Row r: res)
        list.push_back({
            r[0].get<int>(),
            r[1].get<int>(),
            r[2].get<int>(),
            r[3].get<int>(),
            r[4].get<std::string>()
        });
    return list;
}

bool updateCinema(int id, const std::string &name, const std::string &city) {
    auto s = createSession();
    auto t = s->getSchema("TicketBookingSystem").getTable("cinema");

    return t.update()
           .set("name", name)
           .set("city", city)
           .where("id = :i").bind("i", id)
           .execute().getAffectedItemsCount() == 1;
}

bool updateHall(int id, const std::string &name, int seatsPerRow, int rowCount) {
    auto s = createSession();
    auto t = s->getSchema("TicketBookingSystem").getTable("hall");

    return t.update()
           .set("name", name)
           .set("seats_per_row", seatsPerRow)
           .set("row_count", rowCount)
           .where("id = :i").bind("i", id)
           .execute().getAffectedItemsCount() == 1;
}

bool updateMovie(int id, const std::string &title, const std::string &language, const std::string &genre, const std::string &releaseDate, int durationMin) {
    auto s = createSession();
    auto t = s->getSchema("TicketBookingSystem").getTable("movie");

    return t.update()
           .set("title", title)
           .set("language", language)
           .set("genre", genre)
           .set("release_date", releaseDate)
           .set("duration_min", durationMin)
           .where("id = :i").bind("i", id)
           .execute().getAffectedItemsCount() == 1;
}

bool updateShowtime(int id, const std::string &startTime, double price) {
    auto s = createSession();
    auto t = s->getSchema("TicketBookingSystem").getTable("showtime");

    return t.update()
           .set("start_time", startTime)
           .set("price", price)
           .where("id = :i").bind("i", id)
           .execute().getAffectedItemsCount() == 1;
}

std::vector<Seat> fetchSeatsForShow(int showId) {
    std::vector<Seat> v;
    auto s = createSession();
    auto res = s->sql(
                "SELECT s.id, s.row_no, s.col_no, st.name, "
                "EXISTS(SELECT 1 FROM ticket t "
                "       JOIN booking b ON b.id=t.booking_id "
                "       WHERE t.seat_id=s.id AND b.showtime_id=? ) AS taken "
                "FROM seat s "
                "JOIN seat_type st ON st.id=s.seat_type_id "
                "JOIN showtime stt ON stt.hall_id=s.hall_id "
                "WHERE stt.id=? "
                "ORDER BY s.row_no, s.col_no")
            .bind(showId).bind(showId).execute();

    for (mysqlx::Row r: res)
        v.push_back({
            r[0].get<int>(),
            r[1].get<int>(),
            r[2].get<int>(),
            r[3].get<std::string>(),
            r[4].get<bool>()
        });
    return v;
}

SeatType getSeatTypeByName(const std::string &n) {
    auto s = createSession();
    auto row = s->getSchema("TicketBookingSystem")
            .getTable("seat_type")
            .select("id", "price")
            .where("name=:n").bind("n", n).execute().fetchOne();
    return {row[0].get<int>(), n, row[1].get<double>()};
}

bool reserveSeats(int userId, int showId, const std::vector<int> &seatIds, bool payNow) {
    if (seatIds.empty()) return false;

    auto s = createSession();
    s->startTransaction();

    mysqlx::Table seatT = s->getSchema("TicketBookingSystem").getTable("seat");
    mysqlx::SqlStatement check = s->sql(
        "SELECT COUNT(*) FROM ticket t "
        "JOIN booking b ON b.id = t.booking_id "
        "WHERE b.showtime_id = ? AND t.seat_id = ?");
    for (int sid: seatIds) {
        if (check.bind(showId).bind(sid).execute().fetchOne()[0].get<int>() > 0) {
            s->rollback();
            return false;
        }
    }

    double total = 0.0;
    for (int sid: seatIds) {
        auto row = seatT.select("seat_type_id")
                .where("id=:i").bind("i", sid).execute().fetchOne();
        int typeId = row[0].get<int>();
        auto priceRow = s->getSchema("TicketBookingSystem").getTable("seat_type")
                .select("price").where("id=:i")
                .bind("i", typeId).execute().fetchOne();
        total += priceRow[0].get<double>();
    }

    std::string status = payNow ? "paid" : "reserved";
    auto bookingId = s->getSchema("TicketBookingSystem").getTable("booking")
            .insert("user_id", "showtime_id", "status", "total_price")
            .values(userId, showId, status, total)
            .execute().getAutoIncrementValue();

    auto ticketT = s->getSchema("TicketBookingSystem").getTable("ticket");
    for (int sid: seatIds)
        ticketT.insert("booking_id", "seat_id").values(bookingId, sid).execute();

    s->commit();
    return true;
}

void sendMail(const std::string &to, const std::string &subject, const std::string &body) {
    std::ofstream f("last_mail.txt");
    f << "To: " << to << "\nSubject: " << subject << "\n\n" << body;
}

std::vector<Movie> searchMovies(const std::string &title, const std::string &language, const std::string &genre, const std::string &releaseDate) {
    std::vector<Movie> list;
    auto s = createSession();

    std::string sql =
            "SELECT id, title, language, genre, "
            "       DATE_FORMAT(release_date,'%Y-%m-%d') "
            "FROM   movie WHERE 1";

    std::vector<mysqlx::Value> params;

    if (!title.empty()) {
        sql += " AND title LIKE ?";
        params.emplace_back("%" + title + "%");
    }
    if (!language.empty()) {
        sql += " AND language LIKE ?";
        params.emplace_back("%" + language + "%");
    }
    if (!genre.empty()) {
        sql += " AND genre LIKE ?";
        params.emplace_back("%" + genre + "%");
    }
    if (!releaseDate.empty()) {
        sql += " AND release_date = ?";
        params.emplace_back(releaseDate);
    }

    auto stmt = s->sql(sql);
    for (auto &v: params) stmt.bind(v);

    auto res = stmt.execute();
    for (mysqlx::Row r: res)
        list.push_back({
            r[0].get<int>(), r[1].get<std::string>(),
            r[2].get<std::string>(), r[3].get<std::string>(),
            r[4].get<std::string>()
        });
    return list;
}

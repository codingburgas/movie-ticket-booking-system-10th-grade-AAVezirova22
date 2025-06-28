#include "../include/mainMenu.h"
#include "../include/login.h"
#include "../include/register.h"
#include "../include/db.h"

#include <fstream>
#include <iomanip>
#include <iostream>
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
    std::string   line;

    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }
}

void Menu::drawMainMenu()
{
    std::ifstream file("../assets/drawMainMenu.txt");
    std::string   line;

    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }
}

void Menu::drawUserMenu()
{
    std::ifstream file("../assets/drawUserMenu.txt");
    std::string line;

    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }
}

void Menu::drawAdminMenu()
{
    std::ifstream file("../assets/drawAdminMenu.txt");
    std::string   line;

    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }
}

void Menu::displayMainMenu()
{
    while (true)
    {
        clearScreen();
        drawTeamName();
        drawMainMenu();

        std::cin >> choice;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
            {
                auto user = loginUser();
                if (user)
                {
                    if (user->isAdmin())
                    {
                        displayAdminMenu(*user);
                    }
                    else
                    {
                        displayUserMenu(*user);
                    }
                }
                break;
            }
            case 2:
            {
                registerUser();
                break;
            }
            case 3:
            {
                viewMoviesMenu();
                break;
            }
            case 4:
            {
                std::cout << std::endl
                          << "Exiting..." << std::endl;
                return;
            }
            default:
            {
                std::cout << std::endl
                          << "Invalid input." << std::endl;
                break;
            }
        }

        std::cout << std::endl << "Press <Enter> to continue...";
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

    switch (choice)
    {
        case 1:
        {
            viewMoviesMenu();
            break;
        }
        case 2:
        {
            std::cout << std::endl
                      << "Logging out..." << std::endl;
            return;
        }
        default:
        {
            std::cout << "Invalid input." << std::endl;
            break;
        }
    }
}

void Menu::displayAdminMenu(const User& currentUser)
{
    loggedUser = currentUser;

    while (true)
    {
        clearScreen();
        drawTeamName();
        drawAdminMenu();


        std::cin >> choice;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
            case 1:  promoteUser();        break;
            case 2:  demoteUser();         break;
            case 3:  addCinemaMenu();      break;
            case 4:  addHallMenu();        break;
            case 5:  addMovieMenu();       break;
            case 6:  addShowtimeMenu();    break;
            case 7:  listCinemasMenu();    break;
            case 8:  listMoviesMenu();     break;
            case 9:  listShowtimesMenu();  break;
            case 10: editCinemaMenu();       break;
            case 11: editHallMenu();         break;
            case 12: editMovieMenu();        break;
            case 13: editShowtimeMenu();     break;
            case 14: deleteCinemaMenu();     break;
            case 15: deleteHallMenu();       break;
            case 16: deleteMovieMenu();      break;
            case 17: deleteShowtimeMenu();   break;
            case 18:
            {
                std::cout << "Logging out..." << std::endl;
                return;
            }
            default:
            {
                std::cout << "Invalid input." << std::endl;
                break;
            }
        }

        std::cout << "Press <Enter> to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
}

void Menu::promoteUser()
{
    std::vector<User> users = fetchAllUsers();

    std::cout << std::endl
              << "ID  Username        Role" << std::endl
              << "---------------------------------" << std::endl;

    for (const User& u : users)
    {
        std::cout << std::left << std::setw(4) << u.id
                  << std::setw(16) << u.username
                  << u.role << std::endl;
    }

    int id{};
    std::cout << std::endl
              << "Enter user ID to promote: ";
    std::cin >> id;

    if (changeUserRole(id, "admin"))
    {
        std::cout << "Promotion successful." << std::endl;
    }
    else
    {
        std::cout << "Promotion failed." << std::endl;
    }
}

void Menu::demoteUser()
{
    std::vector<User> users = fetchAllUsers();

    std::cout << std::endl
              << "ID  Username" << std::endl
              << "----------------------" << std::endl;

    for (const User& u : users)
    {
        if (u.isAdmin())
        {
            std::cout << std::left << std::setw(4) << u.id
                      << u.username << std::endl;
        }
    }

    int id{};
    std::cout << std::endl
              << "Enter admin ID to demote: ";
    std::cin >> id;

    if (id == loggedUser.id)
    {
        std::cout << "You cannot demote yourself." << std::endl;
        return;
    }

    if (changeUserRole(id, "user"))
    {
        std::cout << "Demotion successful." << std::endl;
    }
    else
    {
        std::cout << "Demotion failed." << std::endl;
    }
}

void Menu::addCinemaMenu()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string name;
    std::string city;

    std::cout << std::endl
              << "Cinema name: ";
    std::getline(std::cin, name);

    std::cout << "City: ";
    std::getline(std::cin, city);

    if (addCinema(name, city))
    {
        std::cout << "Cinema added." << std::endl;
    }
    else
    {
        std::cout << "Failed to add cinema." << std::endl;
    }
}

void Menu::addHallMenu()
{
    int cinemaId{};
    int seats{};
    int rows{};
    std::string hallName;

    std::vector<Cinema> cinemas = fetchAllCinemas();
    if (cinemas.empty())
    {
        std::cout << "No cinemas available." << std::endl;
        return;
    }

    std::cout << std::endl << "Cinemas:" << std::endl;

    for (const Cinema& c : cinemas)
    {
        std::cout << c.id << " — " << c.name << " (" << c.city << ")" << std::endl;
    }

    std::cout << "Cinema ID: ";
    std::cin >> cinemaId;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Hall name: ";
    std::getline(std::cin, hallName);

    std::cout << "Seats per row: ";
    std::cin >> seats;

    std::cout << "Row count: ";
    std::cin >> rows;

    if (addHall(cinemaId, hallName, seats, rows))
    {
        std::cout << "Hall added." << std::endl;
    }
    else
    {
        std::cout << "Failed to add hall." << std::endl;
    }
}

void Menu::addMovieMenu()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string title;
    std::string language;
    std::string genre;
    std::string date;
    int duration{};

    std::cout << std::endl << "Title: ";
    std::getline(std::cin, title);

    std::cout << "Language: ";
    std::getline(std::cin, language);

    std::cout << "Genre: ";
    std::getline(std::cin, genre);

    std::cout << "Release date (YYYY-MM-DD): ";
    std::getline(std::cin, date);

    std::cout << "Duration (minutes): ";
    std::cin >> duration;

    if (addMovie(title, language, genre, date, duration))
    {
        std::cout << "Movie added." << std::endl;
    }
    else
    {
        std::cout << "Failed to add movie." << std::endl;
    }
}

void Menu::addShowtimeMenu()
{
    int cinemaId{};
    int hallId{};
    int movieId{};
    double price{};
    std::string startISO;

    std::vector<Cinema> cinemas = fetchAllCinemas();
    if (cinemas.empty())
    {
        std::cout << "No cinemas available." << std::endl;
        return;
    }

    std::cout << std::endl << "Cinemas:" << std::endl;

    for (const Cinema& c : cinemas)
    {
        std::cout << c.id << " — " << c.name << std::endl;
    }

    std::cout << "Cinema ID: ";
    std::cin >> cinemaId;

    std::vector<Hall> halls = fetchHallsByCinema(cinemaId);
    if (halls.empty())
    {
        std::cout << "No halls for that cinema." << std::endl;
        return;
    }

    std::cout << std::endl  << "Halls:" << std::endl;

    for (const Hall& h : halls)
    {
        std::cout << h.id << " — " << h.name << std::endl;
    }

    std::cout << "Hall ID: ";
    std::cin >> hallId;

    std::vector<Movie> movies = fetchAllMovies();
    if (movies.empty())
    {
        std::cout << "No movies available." << std::endl;
        return;
    }

    std::cout << std::endl << "Movies:" << std::endl;

    for (const Movie& m : movies)
    {
        std::cout << m.id << " — " << m.title << std::endl;
    }

    std::cout << "Movie ID: ";
    std::cin >> movieId;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Start time (YYYY-MM-DD HH:MM): ";
    std::getline(std::cin, startISO);

    std::cout << "Price: ";
    std::cin >> price;

    if (addShowtime(hallId, movieId, startISO, price))
    {
        std::cout << "Showtime added." << std::endl;
    }
    else
    {
        std::cout << "Failed to add showtime." << std::endl;
    }
}

void Menu::listCinemasMenu()
{
    std::vector<Cinema> cinemas = fetchAllCinemas();

    if (cinemas.empty())
    {
        std::cout << "No cinemas." << std::endl;
        return;
    }

    for (const Cinema& c : cinemas)
    {
        std::cout << c.id << "  " << c.name << " (" << c.city << ")" << std::endl;
    }
}

void Menu::listMoviesMenu()
{
    std::vector<Movie> movies = fetchAllMovies();

    if (movies.empty())
    {
        std::cout << "No movies." << std::endl;
        return;
    }

    for (const Movie& m : movies)
    {
        std::cout << m.id << "  " << m.title << " — " << m.genre << " — " << m.language << " — " << m.releaseDate << std::endl;
    }
}

void Menu::listShowtimesMenu()
{
    std::vector<Cinema> cinemas = fetchAllCinemas();
    if (cinemas.empty())
    {
        std::cout << "No cinemas." << std::endl;
        return;
    }

    for (const Cinema& c : cinemas)
        std::cout << c.id << " — " << c.name << std::endl;

    int cinemaId {};
    std::cout << "Cinema ID: ";
    std::cin  >> cinemaId;

    std::vector<Showtime> shows = fetchShowtimesByCinema(cinemaId);
    if (shows.empty())
    {
        std::cout << "No showtimes for this cinema." << std::endl;
        return;
    }

    std::vector<Movie> movies = fetchAllMovies();
    std::unordered_map<int, std::string> idToTitle;
    for (const Movie& m : movies) idToTitle[m.id] = m.title;

    struct MovieBlock
    {
        std::vector<std::string> times;
        double                   price {};
    };
    std::map<std::string, MovieBlock> listing;

    for (const Showtime& s : shows)
    {
        auto it = idToTitle.find(s.movieId);
        if (it == idToTitle.end()) continue;

        std::string title = it->second;

        std::string time;
        std::size_t pos = s.startISO.find(' ');
        if (pos != std::string::npos && pos + 6 <= s.startISO.size())
            time = s.startISO.substr(pos + 1, 5);
        else
            time = s.startISO;

        listing[title].times.push_back(time);
        listing[title].price = s.price;
    }

    std::cout << std::endl;
    for (const auto& [title, block] : listing)
    {
        std::cout << title << ": ";

        for (std::size_t i = 0; i < block.times.size(); ++i)
        {
            std::cout << block.times[i];
            if (i + 1 < block.times.size()) std::cout << ", ";
        }
        std::cout << std::endl
                  << "Price: "
                  << std::fixed << std::setprecision(2)
                  << block.price << std::endl << std::endl;
    }
}

void Menu::viewMoviesMenu()
{
    std::vector<Cinema> cinemas = fetchAllCinemas();
    if (cinemas.empty())
    {
        std::cout << "No cinemas available." << std::endl;
        return;
    }
    for (const Cinema& c : cinemas)
        std::cout << c.id << " — " << c.name << std::endl;

    int cinemaId {};
    std::cout << "Cinema ID: ";
    std::cin  >> cinemaId;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    auto     now      = std::chrono::system_clock::now();
    std::time_t tt    = std::chrono::system_clock::to_time_t(now);
    std::tm     tmNow = *std::localtime(&tt);

    std::ostringstream todayBuf;
    todayBuf << std::put_time(&tmNow, "%Y-%m-%d");
    std::string today = todayBuf.str();

    std::string dateFilter = today;
    std::cout << "Date to view [" << today << "] (YYYY-MM-DD): ";
    std::string input;
    std::getline(std::cin, input);
    if (!input.empty()) dateFilter = input;

    std::string sql;
    if (dateFilter == today)
        sql =
            "SELECT m.title, DATE_FORMAT(st.start_time,'%H:%i'), st.price "
            "FROM   showtime st "
            "JOIN   hall h   ON h.id = st.hall_id "
            "JOIN   movie m  ON m.id = st.movie_id "
            "WHERE  h.cinema_id = ? "
            "AND    DATE(st.start_time) = CURDATE() "
            "AND    st.start_time > NOW() "
            "ORDER  BY st.start_time";
    else
        sql =
            "SELECT m.title, DATE_FORMAT(st.start_time,'%H:%i'), st.price "
            "FROM   showtime st "
            "JOIN   hall h   ON h.id = st.hall_id "
            "JOIN   movie m  ON m.id = st.movie_id "
            "WHERE  h.cinema_id = ? "
            "AND    DATE(st.start_time) = ? "
            "ORDER  BY st.start_time";

    auto session = createSession();
    mysqlx::SqlStatement stmt = session->sql(sql);
    stmt.bind(cinemaId);
    if (dateFilter != today) stmt.bind(dateFilter);
    auto res = stmt.execute();

    std::map<std::string, std::pair<std::vector<std::string>, double>> block;
    for (const mysqlx::Row& r : res)
    {
        std::string title = r[0].get<std::string>();
        std::string time  = r[1].get<std::string>();
        double      price = r[2].get<double>();
        block[title].first.push_back(time);
        block[title].second = price;
    }

    if (block.empty())
    {
        std::cout << "No upcoming showtimes for that day." << std::endl;
        return;
    }

    std::cout << std::endl;
    for (const auto& [title, data] : block)
    {
        const std::vector<std::string>& times = data.first;
        std::cout << title << ": ";
        for (std::size_t i = 0; i < times.size(); ++i)
        {
            std::cout << times[i];
            if (i + 1 < times.size()) std::cout << ", ";
        }
        std::cout << std::endl
                  << "Price: " << std::fixed << std::setprecision(2)
                  << data.second << std::endl << std::endl;
    }
}

void Menu::editCinemaMenu()
{
    listCinemasMenu();
    int id {};
    std::cout << "Cinema ID to edit: ";
    std::cin  >> id;

    std::vector<Cinema> cinemas = fetchAllCinemas();
    auto it = std::find_if(cinemas.begin(), cinemas.end(),
                           [id](const Cinema& c){ return c.id == id; });
    if (it == cinemas.end())
    {
        std::cout << "Cinema not found." << std::endl;
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string name  = it->name;
    std::string city  = it->city;
    std::string input;

    std::cout << "New name  [" << name << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) name = input;

    std::cout << "New city  [" << city << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) city = input;

    if (updateCinema(id, name, city))
        std::cout << "Cinema updated." << std::endl;
    else
        std::cout << "Update failed." << std::endl;
}

void Menu::editHallMenu()
{
    listCinemasMenu();
    int cinemaId {};
    std::cout << "Cinema ID: ";
    std::cin  >> cinemaId;

    std::vector<Hall> halls = fetchHallsByCinema(cinemaId);
    if (halls.empty())
    {
        std::cout << "No halls for that cinema." << std::endl;
        return;
    }

    for (const Hall& h : halls)
        std::cout << h.id << " — " << h.name << std::endl;

    int id {};
    std::cout << "Hall ID to edit: ";
    std::cin  >> id;

    auto it = std::find_if(halls.begin(), halls.end(),
                           [id](const Hall& h){ return h.id == id; });
    if (it == halls.end())
    {
        std::cout << "Hall not found." << std::endl;
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string name = it->name, input;
    int seats = it->seatsPerRow;
    int rows  = it->rowCount;

    std::cout << "New name [" << name << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) name = input;

    std::cout << "Seats per row [" << seats << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) seats = std::stoi(input);

    std::cout << "Row count [" << rows << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) rows = std::stoi(input);

    if (updateHall(id, name, seats, rows))
        std::cout << "Hall updated." << std::endl;
    else
        std::cout << "Update failed." << std::endl;
}

void Menu::editMovieMenu()
{
    listMoviesMenu();
    int id {};
    std::cout << "Movie ID to edit: ";
    std::cin  >> id;

    std::vector<Movie> movies = fetchAllMovies();
    auto it = std::find_if(movies.begin(), movies.end(),
                           [id](const Movie& m){ return m.id == id; });
    if (it == movies.end())
    {
        std::cout << "Movie not found." << std::endl;
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string title = it->title;
    std::string lang  = it->language;
    std::string genre = it->genre;
    std::string date  = it->releaseDate;
    int         dur   = 0;
    try { dur = std::stoi(it->releaseDate); } catch (...) {}

    std::string input;

    std::cout << "New title [" << title << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) title = input;

    std::cout << "New language [" << lang << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) lang = input;

    std::cout << "New genre [" << genre << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) genre = input;

    std::cout << "New release YYYY-MM-DD [" << date << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) date = input;

    std::cout << "New duration min [" << it->releaseDate << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) dur = std::stoi(input);

    if (updateMovie(id, title, lang, genre, date, dur))
        std::cout << "Movie updated." << std::endl;
    else
        std::cout << "Update failed." << std::endl;
}

void Menu::editShowtimeMenu()
{
    std::vector<Cinema> cinemas = fetchAllCinemas();
    if (cinemas.empty())
    {
        std::cout << "No cinemas." << std::endl;
        return;
    }
    for (const Cinema& c : cinemas)
        std::cout << c.id << " — " << c.name << std::endl;

    int cinemaId{};
    std::cout << "Cinema ID: ";
    std::cin >> cinemaId;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<Showtime> shows = fetchShowtimesByCinema(cinemaId);
    if (shows.empty())
    {
        std::cout << "No showtimes for this cinema." << std::endl;
        return;
    }

    std::vector<Movie> movies = fetchAllMovies();
    std::unordered_map<int, std::string> idToTitle;
    for (const Movie& m : movies) idToTitle[m.id] = m.title;

    std::cout << std::endl << "ID  Title            Time  Price" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    for (const Showtime& s : shows)
    {
        std::cout << std::left << std::setw(4)  << s.id
                  << std::setw(16)              << idToTitle[s.movieId]
                  << std::setw(6)               << s.startISO
                  << std::fixed << std::setprecision(2)
                  << s.price << std::endl;
    }

    int id{};
    std::cout << std::endl << "Showtime ID to edit: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    auto session = createSession();
    auto row = session->sql(
                   "SELECT DATE_FORMAT(start_time,'%Y-%m-%d %H:%i'), price "
                   "FROM showtime WHERE id = ?")
                   .bind(id).execute().fetchOne();

    if (!row)
    {
        std::cout << "Showtime not found." << std::endl;
        return;
    }

    std::string start = row[0].get<std::string>();
    double      price = row[1].get<double>();
    std::string input;

    std::cout << "New start YYYY-MM-DD HH:MM [" << start << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) start = input;

    std::cout << "New price [" << std::fixed << std::setprecision(2)
              << price << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) price = std::stod(input);

    if (updateShowtime(id, start, price))
        std::cout << "Showtime updated." << std::endl;
    else
        std::cout << "Update failed." << std::endl;
}


void Menu::deleteCinemaMenu()
{
    listCinemasMenu();
    int id; std::cout << "Cinema ID to delete: "; std::cin >> id;
    if (deleteCinema(id)) std::cout << "Cinema deleted." << std::endl;
    else std::cout << "Delete failed." << std::endl;
}

void Menu::deleteHallMenu()
{
    int cinemaId; listCinemasMenu();
    std::cout << "Cinema ID: "; std::cin >> cinemaId;
    std::vector<Hall> halls = fetchHallsByCinema(cinemaId);
    for (const Hall& h : halls) std::cout << h.id << " — " << h.name << std::endl;
    int id; std::cout << "Hall ID to delete: "; std::cin >> id;
    if (deleteHall(id)) std::cout << "Hall deleted." << std::endl;
    else std::cout << "Delete failed." << std::endl;
}

void Menu::deleteMovieMenu()
{
    listMoviesMenu();
    int id; std::cout << "Movie ID to delete: "; std::cin >> id;
    if (deleteMovie(id)) std::cout << "Movie deleted." << std::endl;
    else std::cout << "Delete failed." << std::endl;
}

void Menu::deleteShowtimeMenu()
{
    std::vector<Cinema> cinemas = fetchAllCinemas();
    if (cinemas.empty())
    {
        std::cout << "No cinemas." << std::endl;
        return;
    }
    for (const Cinema& c : cinemas)
        std::cout << c.id << " — " << c.name << std::endl;

    int cinemaId{};
    std::cout << "Cinema ID: ";
    std::cin >> cinemaId;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<Showtime> shows = fetchShowtimesByCinema(cinemaId);
    if (shows.empty())
    {
        std::cout << "No showtimes for this cinema." << std::endl;
        return;
    }

    std::vector<Movie> movies = fetchAllMovies();
    std::unordered_map<int, std::string> idToTitle;
    for (const Movie& m : movies) idToTitle[m.id] = m.title;

    std::cout << std::endl << "ID  Title            Time  Price" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    for (const Showtime& s : shows)
    {
        std::cout << std::left << std::setw(4)  << s.id
                  << std::setw(16)              << idToTitle[s.movieId]
                  << std::setw(6)               << s.startISO
                  << std::fixed << std::setprecision(2)
                  << s.price << std::endl;
    }

    int id{};
    std::cout << std::endl << "Showtime ID to delete: ";
    std::cin >> id;

    if (deleteShowtime(id))
        std::cout << "Showtime deleted." << std::endl;
    else
        std::cout << "Delete failed." << std::endl;
}
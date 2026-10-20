#include "SqliteRepository.h"
#include <iostream>

// Callback function used by sqlite3_exec to read SELECT query results
static int loadDatabaseCallback(void* data, int argc, char** argv, char** azColName) {
    std::vector<Movie>* movies = static_cast<std::vector<Movie>*>(data);

    std::string title = argv[0] ? argv[0] : "";
    std::string genre = argv[1] ? argv[1] : "";
    int year = argv[2] ? std::stoi(argv[2]) : 0;
    int likes = argv[3] ? std::stoi(argv[3]) : 0;
    std::string trailer = argv[4] ? argv[4] : "";

    movies->push_back(Movie(title, genre, year, likes, trailer));
    return 0;
}

void SqliteRepository::loadFromDatabase() {
    this->movies.clear();
    std::string sql = "SELECT Title, Genre, Year, Likes, Trailer FROM Movies;";
    char* errMsg = nullptr;

    sqlite3_exec(db, sql.c_str(), loadDatabaseCallback, &this->movies, &errMsg);
}

SqliteRepository::SqliteRepository(const std::string& dbPath) : Repository("") {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        throw RepositoryException("Error: Cannot open database!");
    }

    std::string sql = "CREATE TABLE IF NOT EXISTS Movies ("
        "Title TEXT PRIMARY KEY, "
        "Genre TEXT, "
        "Year INTEGER, "
        "Likes INTEGER, "
        "Trailer TEXT);";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        sqlite3_free(errMsg);
    }

    loadFromDatabase();
}

SqliteRepository::~SqliteRepository() {
    sqlite3_close(db);
}

void SqliteRepository::add(const Movie& m) {
    Repository::add(m);

    std::string sql = "INSERT INTO Movies (Title, Genre, Year, Likes, Trailer) VALUES ('" +
        m.getTitle() + "', '" + m.getGenre() + "', " +
        std::to_string(m.getYear()) + ", " +
        std::to_string(m.getLikes()) + ", '" +
        m.getTrailer() + "');";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::string error(errMsg);
        sqlite3_free(errMsg);
        // If DB fails, remove it from the vector to maintain consistency
        this->movies.pop_back();
        throw RepositoryException("SQL Error: " + error);
    }
}

void SqliteRepository::remove(std::vector<Movie>::const_iterator it) {
    std::string title = it->getTitle(); // Save title before removing from vector

    Repository::remove(it);

    std::string sql = "DELETE FROM Movies WHERE Title = '" + title + "';";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        sqlite3_free(errMsg);
    }
}

void SqliteRepository::update(const std::string& title, const std::string& new_genre, int new_year, int new_likes, const std::string& new_trailer) {
    Repository::update(title, new_genre, new_year, new_likes, new_trailer);

    std::string sql = "UPDATE Movies SET Genre = '" + new_genre +
        "', Year = " + std::to_string(new_year) +
        ", Likes = " + std::to_string(new_likes) +
        ", Trailer = '" + new_trailer +
        "' WHERE Title = '" + title + "';";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        sqlite3_free(errMsg);
    }
}
#pragma once
#include "Repository.h"
#include "sqlite3.h"

class SqliteRepository : public Repository
{
private:
    sqlite3* db;

    void loadFromDatabase();

protected:
    // Override the file save method to do nothing, preventing text file creation
    void saveToFile() const override {}

public:
    SqliteRepository(const std::string& dbPath);

    ~SqliteRepository() override;

    void add(const Movie& m) override;
    void remove(std::vector<Movie>::const_iterator it) override;
    void update(const std::string& title, const std::string& new_genre, int new_year, int new_likes, const std::string& new_trailer) override;
};
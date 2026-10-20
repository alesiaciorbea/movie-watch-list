#pragma once
#include "Movie.h"
#include <vector>
#include <string>

class FileWatchlist
{
protected:
    std::vector<Movie> movies;
    std::string filename;

public:
    FileWatchlist(const std::string& filename) : filename(filename) {}
    virtual ~FileWatchlist() {}

    void add(const Movie& m) {
        this->movies.push_back(m);
        this->writeToFile();
    }

    void remove(std::vector<Movie>::const_iterator it) {
        this->movies.erase(it);
        this->writeToFile();
    }

    const std::vector<Movie>& getMovies() const {
        return this->movies;
    }

    virtual void writeToFile() const = 0;
    virtual void displayWatchlist() const = 0;
};
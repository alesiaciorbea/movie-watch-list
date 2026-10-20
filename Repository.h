#pragma once
#include "Exceptions.h"
#include "Movie.h"
#include <vector>
#include <string>

class Repository
{
protected:
    std::vector<Movie> movies;
    std::string filename;

    virtual void loadFromFile();
    virtual void saveToFile() const;

public:
    Repository(const std::string& filename);

    virtual ~Repository() = default;

    size_t size() const;

    const Movie& getMovie(int index) const;

    const std::vector<Movie>& getMovies() const;

    std::vector<Movie>::const_iterator findByTitle(const std::string& title) const;

    virtual void add(const Movie& m);

    virtual void remove(std::vector<Movie>::const_iterator it);

    virtual void update(const std::string& title, const std::string& new_genre, int new_year, int new_likes, const std::string& new_trailer);
};
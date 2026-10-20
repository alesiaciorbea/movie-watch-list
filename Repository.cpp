#include "Repository.h"
#include "MovieValidator.h"
#include <stdexcept>
#include <fstream>

void Repository::loadFromFile()
{
    std::ifstream file(this->filename);

    if (!file.is_open())
        return;

    Movie m;
    while (file >> m)
    {
        this->movies.push_back(m);
    }

    file.close();
}

void Repository::saveToFile() const
{
    std::ofstream file(this->filename);

    for (const auto& m : this->movies)
    {
        file << m << "\n";
    }

    file.close();
}

Repository::Repository(const std::string& filename)
{
    this->filename = filename;
    this->loadFromFile();
}

size_t Repository::size() const
{
    return this->movies.size();
}

const Movie& Repository::getMovie(int index) const
{
    return this->movies.at(index);
}

std::vector<Movie>::const_iterator Repository::findByTitle(const std::string& title) const
{
    return std::find_if(this->movies.begin(), this->movies.end(), [&title](const Movie& m) {return m.getTitle() == title; });

}

void Repository::add(const Movie& m)
{
    MovieValidator::validate(m);

    if (findByTitle(m.getTitle()) != this->movies.end())
    {
        throw RepositoryException("A movie with this title already exists in the database!");
    }
    this->movies.push_back(m);
    this->saveToFile();
}

void Repository::remove(std::vector<Movie>::const_iterator it)
{

    this->movies.erase(it);
    this->saveToFile();
}

void Repository::update(const std::string& title, const std::string& new_genre, int new_year, int new_likes, const std::string& new_trailer)
{
    Movie movieToValidate(title, new_genre, new_year, new_likes, new_trailer);

    MovieValidator::validate(movieToValidate);

    auto it = std::find_if(this->movies.begin(), this->movies.end(), [&title](const Movie& m) {
        return m.getTitle() == title;
        });


    if (it == this->movies.end())
    {
        throw RepositoryException("A movie with this title does not exist!");
    }

    it->setGenre(new_genre);
    it->setYear(new_year);
    it->setLikes(new_likes);
    it->setTrailer(new_trailer);

    this->saveToFile();
}

const std::vector<Movie>& Repository::getMovies() const
{
    return this->movies;
}
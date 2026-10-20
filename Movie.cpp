#include "Movie.h"
#include <cstdlib>
#include "Exceptions.h"

Movie::Movie()
{
	this->title = "";
	this->genre = "";
	this->year = 0;
	this->likes = 0;
	this->trailer = "";
}

Movie::Movie(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer)
{
	this->title = title;
	this->genre = genre;
	this->year = year;
	this->likes = likes;
	this->trailer = trailer;
}

std::string Movie::getTitle() const {
	return title;
}

std::string Movie::getGenre() const {
	return genre;
}

int Movie::getYear() const {
	return year;
}

int Movie::getLikes() const {
	return likes;
}

std::string Movie::getTrailer() const {
	return trailer;
}

void Movie::setGenre(const std::string& genre)
{
	this->genre = genre;
}

void Movie::setYear(int year)
{
	this->year = year;
}

void Movie::setLikes(int likes)
{
	this->likes = likes;
}

void Movie::setTrailer(const std::string& trailer)
{
	this->trailer = trailer;
}

bool Movie::operator==(const Movie& m) const
{
	return this->title == m.title;
}

void Movie::playTrailer() const
{
	std::string command = "start " + this->trailer;
	system(command.c_str());
}

std::istream& operator>>(std::istream& is, Movie& m)
{
	std::string yearStr, likesStr;

	if (std::getline(is, m.title, ',') &&
		std::getline(is, m.genre, ',') &&
		std::getline(is, yearStr, ',') &&
		std::getline(is, likesStr, ','))
	{
		std::getline(is, m.trailer);

		m.year = std::stoi(yearStr);
		m.likes = std::stoi(likesStr);
	}

	return is;
}

std::ostream& operator<<(std::ostream& os, const Movie& m)
{
	os << m.title << "," << m.genre << "," << m.year << "," << m.likes << "," << m.trailer;
	return os;
}

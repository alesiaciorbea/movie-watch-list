#include "Controller.h"
#include <stdexcept>
#include <algorithm>
#include <iterator>

Controller::Controller(Repository& r, WatchList& w) : repo(r), watchList(w)
{
	if (this->repo.getMovies().empty())
		this->generateInitialMovies();
}

void Controller::generateInitialMovies()
{
	this->repo.add(Movie("The Matrix", "Sci-Fi", 1999, 15000, "https://www.youtube.com/watch?v=vKQi3bBA1y8"));
	this->repo.add(Movie("Inception", "Sci-Fi", 2010, 20000, "https://www.youtube.com/watch?v=YoHD9XEInc0"));
	this->repo.add(Movie("The Godfather", "Crime", 1972, 18000, "https://www.youtube.com/watch?v=sY1S34973zA"));
	this->repo.add(Movie("Pulp Fiction", "Crime", 1994, 16000, "https://www.youtube.com/watch?v=s7EdQ4FqbhY"));
	this->repo.add(Movie("Interstellar", "Sci-Fi", 2014, 25000, "https://www.youtube.com/watch?v=zSWdZVtXT7E"));
	this->repo.add(Movie("Parasite", "Thriller", 2019, 12000, "https://www.youtube.com/watch?v=5xH0HfJHsaY"));
	this->repo.add(Movie("The Dark Knight", "Action", 2008, 30000, "https://www.youtube.com/watch?v=EXeTwQWrcwY"));
	this->repo.add(Movie("Fight Club", "Drama", 1999, 14000, "https://www.youtube.com/watch?v=qtRKdVHc-cE"));
	this->repo.add(Movie("Forrest Gump", "Drama", 1994, 22000, "https://www.youtube.com/watch?v=bLvqoHBptjg"));
	this->repo.add(Movie("Gladiator", "Action", 2000, 19000, "https://www.youtube.com/watch?v=owK1qxDselE"));
}

void Controller::addMovie(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer)
{
	Movie m(title, genre, year, likes, trailer);
	this->repo.add(m);

	this->undoStack.push(std::make_unique<ActionAdd>(this->repo, m));

	// Clear Redo stack because a new action was just performed
	while (!this->redoStack.empty()) this->redoStack.pop();
}

void Controller::removeMovie(const std::string& title)
{
	auto it = this->repo.findByTitle(title);
	if (it == this->repo.getMovies().end())
		throw std::invalid_argument("The movie doesn't exist in the data base!");

	Movie deletedMovie = *it;
	this->repo.remove(it);

	this->undoStack.push(std::make_unique<ActionRemove>(this->repo, deletedMovie));
	while (!this->redoStack.empty()) this->redoStack.pop();
}

void Controller::updateMovie(const std::string& title, const std::string& new_genre, int new_year, int new_likes, const std::string& new_trailer)
{
	auto it = this->repo.findByTitle(title);
	if (it == this->repo.getMovies().end())
		throw std::invalid_argument("The movie doesn't exist in the data base!");

	Movie oldMovie = *it;
	Movie newMovie(title, new_genre, new_year, new_likes, new_trailer);

	this->repo.update(title, new_genre, new_year, new_likes, new_trailer);

	this->undoStack.push(std::make_unique<ActionUpdate>(this->repo, oldMovie, newMovie));
	while (!this->redoStack.empty()) this->redoStack.pop();
}

void Controller::undo()
{
	if (this->undoStack.empty()) {
		throw std::runtime_error("No more actions to undo!");
	}

	std::unique_ptr<Action> lastAction = std::move(this->undoStack.top());
	this->undoStack.pop();

	lastAction->executeUndo();

	this->redoStack.push(std::move(lastAction));
}

void Controller::redo()
{
	if (this->redoStack.empty()) {
		throw std::runtime_error("No more actions to redo!");
	}

	std::unique_ptr<Action> lastAction = std::move(this->redoStack.top());
	this->redoStack.pop();

	lastAction->executeRedo();

	this->undoStack.push(std::move(lastAction));
}

std::vector<Movie> Controller::filterGenre(const std::string& genre) const
{
	const std::vector<Movie>& allMovies = this->repo.getMovies();
	std::vector<Movie> filter;

	if (genre == "")
		return allMovies;

	std::copy_if(allMovies.begin(), allMovies.end(),
		std::back_inserter(filter), [&genre](const Movie& m) {
			return m.getGenre() == genre; });

	return filter;
}

void Controller::removeWatchListItem(int index, int review)
{
	Movie m = this->watchList.getMovie(index);
	auto itWatchList = this->watchList.getWatchList().begin() + index;
	this->watchList.removeFromWatchList(itWatchList);

	if (review == 1) {
		auto itRepo = this->repo.findByTitle(m.getTitle());
		if (itRepo != this->repo.getMovies().end()) {
			this->repo.update(m.getTitle(), itRepo->getGenre(), itRepo->getYear(), itRepo->getLikes() + 1, itRepo->getTrailer());
		}
	}
}

void Controller::openWatchlistFile() const
{
	this->watchList.displayWatchlist();
}

void Controller::addMovieToWatchList(const Movie& m)
{
	const std::vector<Movie>& currentList = this->watchList.getWatchList();

	auto it = std::find_if(currentList.begin(), currentList.end(), [&m](const Movie& crt) {
		return crt.getTitle() == m.getTitle();
		});

	if (it != currentList.end()) {
		throw std::runtime_error("Error: This movie is already in your watchlist!");
	}

	this->watchList.addToWatchList(m);
}

Repository& Controller::getRepo() const
{
	return this->repo;
}

WatchList& Controller::getWatchList()
{
	return this->watchList;
}
#pragma once
#include "Repository.h"
#include "WatchList.h"
#include "Action.h"
#include <string>
#include <vector>
#include <stack>

class Controller
{
private:
    Repository& repo;
    WatchList& watchList;
    std::stack<std::unique_ptr<Action>> undoStack;
    std::stack<std::unique_ptr<Action>> redoStack;

    void generateInitialMovies();

public:
    Controller(Repository& r, WatchList& w);

    void addMovie(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer);

    void removeMovie(const std::string& title);

    void updateMovie(const std::string& title, const std::string& new_genre, int new_year, int new_likes, const std::string& new_trailer);

    std::vector<Movie> filterGenre(const std::string& genre) const;

    // If the 'review' parameter is 1, it also increments the like count for that 
    // specific movie in the main Repository.
    void removeWatchListItem(int index, int review);

    void addMovieToWatchList(const Movie& m);

    Repository& getRepo() const;

    WatchList& getWatchList();

    void openWatchlistFile() const;

    void undo();
    void redo();
};
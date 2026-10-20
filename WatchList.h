#pragma once
#include <vector>
#include "Movie.h"
#include "FileWatchlist.h"
class WatchList
{
private:
    FileWatchlist* watchlist;

public:
    WatchList(FileWatchlist* fw);
    ~WatchList();

    const Movie& getMovie(int index) const;

    void addToWatchList(const Movie& m);
    void removeFromWatchList(std::vector<Movie>::const_iterator index);

    const std::vector<Movie>& getWatchList() const;

    void displayWatchlist() const;
};
#include "WatchList.h"

WatchList::WatchList(FileWatchlist* fw)
{
    this->watchlist = fw;
}

WatchList::~WatchList()
{
    delete this->watchlist;
}

const Movie& WatchList::getMovie(int index) const
{
    return this->watchlist->getMovies().at(index);
}

void WatchList::addToWatchList(const Movie& m)
{
    this->watchlist->add(m);
}

void WatchList::removeFromWatchList(std::vector<Movie>::const_iterator index)
{
    this->watchlist->remove(index);
}

const std::vector<Movie>& WatchList::getWatchList() const
{
    return this->watchlist->getMovies();
}

void WatchList::displayWatchlist() const
{
    this->watchlist->displayWatchlist();
}
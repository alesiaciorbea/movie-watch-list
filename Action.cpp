#include "Action.h"

ActionAdd::ActionAdd(Repository& repo, const Movie& movie)
    : repo(repo), addedMovie(movie) {
}

void ActionAdd::executeUndo() {
    auto it = this->repo.findByTitle(this->addedMovie.getTitle());

    if (it != this->repo.getMovies().end()) {
        this->repo.remove(it);
    }
}

void ActionAdd::executeRedo() {
    this->repo.add(this->addedMovie);
}

ActionRemove::ActionRemove(Repository& repo, const Movie& movie)
    : repo(repo), deletedMovie(movie) {
}

void ActionRemove::executeUndo() {
    this->repo.add(this->deletedMovie);
}

void ActionRemove::executeRedo() {
    auto it = this->repo.findByTitle(this->deletedMovie.getTitle());

    if (it != this->repo.getMovies().end()) {
        this->repo.remove(it);
    }
}

ActionUpdate::ActionUpdate(Repository& repo, const Movie& oldMovie, const Movie& newMovie)
    : repo(repo), oldMovie(oldMovie), newMovie(newMovie) {
}

void ActionUpdate::executeUndo() {
    this->repo.update(
        this->oldMovie.getTitle(),
        this->oldMovie.getGenre(),
        this->oldMovie.getYear(),
        this->oldMovie.getLikes(),
        this->oldMovie.getTrailer()
    );
}

void ActionUpdate::executeRedo() {
    this->repo.update(
        this->newMovie.getTitle(),
        this->newMovie.getGenre(),
        this->newMovie.getYear(),
        this->newMovie.getLikes(),
        this->newMovie.getTrailer()
    );
}
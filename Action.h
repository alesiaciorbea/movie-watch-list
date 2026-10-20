#pragma once
#include "Movie.h"
#include "Repository.h"

class Action {
public:
    virtual void executeUndo() = 0;
    virtual void executeRedo() = 0;

    virtual ~Action() = default;
};

class ActionAdd : public Action {
private:
    Movie addedMovie;
    Repository& repo;

public:
    ActionAdd(Repository& repo, const Movie& movie);
    void executeUndo() override;
    void executeRedo() override;
};

class ActionRemove : public Action {
private:
    Movie deletedMovie;
    Repository& repo;

public:
    ActionRemove(Repository& repo, const Movie& movie);
    void executeUndo() override;
    void executeRedo() override;
};

class ActionUpdate : public Action {
private:
    Movie oldMovie;
    Movie newMovie;
    Repository& repo;

public:
    ActionUpdate(Repository& repo, const Movie& oldMovie, const Movie& newMovie);
    void executeUndo() override;
    void executeRedo() override;
};
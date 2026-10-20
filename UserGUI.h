#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include "Controller.h"

class UserGUI : public QWidget
{
    Q_OBJECT

public:
    UserGUI(Controller& controller, QWidget* parent = nullptr);
    void filterMovies();
    void syncData();

private:
    Controller& ctrl;
    std::vector<Movie> currentMovies;
    int currentIndex;

    QLineEdit* editGenreFilter;
    QPushButton* btnFilter;

    QLabel* lblTitle;
    QLabel* lblGenre;
    QLabel* lblYear;
    QLabel* lblLikes;

    QPushButton* btnAddWatchlist;
    QPushButton* btnNext;

    QListWidget* listWatchlist;
    QPushButton* btnOpenFile;

    void initGUI();
    void connectSignals();
    void populateWatchlist();
    void displayMovie();

private slots:
    void nextMovie();
    void addToWatchlist();
    void handleWatchlistRemove(QListWidgetItem* item);
    void openWatchlistFile();
};
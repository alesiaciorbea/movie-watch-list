#include "UserGUI.h"
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>

UserGUI::UserGUI(Controller& controller, QWidget* parent)
    : QWidget(parent), ctrl(controller), currentIndex(0)
{
    this->initGUI();
    this->populateWatchlist();
    this->connectSignals();
}

void UserGUI::initGUI()
{
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    this->setWindowTitle("User Mode - Movie Manager");
    this->resize(700, 400);

    QVBoxLayout* leftLayout = new QVBoxLayout();

    QHBoxLayout* filterLayout = new QHBoxLayout();
    this->editGenreFilter = new QLineEdit();
    this->editGenreFilter->setPlaceholderText("Enter genre (leave empty for all)...");
    this->btnFilter = new QPushButton("Choose genre");
    filterLayout->addWidget(this->editGenreFilter);
    filterLayout->addWidget(this->btnFilter);
    leftLayout->addLayout(filterLayout);

    leftLayout->addWidget(new QLabel("<h3>Now playing / viewing:</h3>"));

    this->lblTitle = new QLabel("<b>Title:</b> Waiting for search...");
    this->lblGenre = new QLabel("<b>Genre:</b> -");
    this->lblYear = new QLabel("<b>Year of release:</b> -");
    this->lblLikes = new QLabel("<b>Number of likes:</b> -");

    leftLayout->addWidget(this->lblTitle);
    leftLayout->addWidget(this->lblGenre);
    leftLayout->addWidget(this->lblYear);
    leftLayout->addWidget(this->lblLikes);

    this->btnAddWatchlist = new QPushButton("Add to Watchlist");
    this->btnNext = new QPushButton("Next");

    leftLayout->addWidget(this->btnAddWatchlist);
    leftLayout->addWidget(this->btnNext);
    leftLayout->addStretch();

    QVBoxLayout* rightLayout = new QVBoxLayout();

    rightLayout->addWidget(new QLabel("<h3>My Watchlist:</h3>"));
    rightLayout->addWidget(new QLabel("<small><i>Double click an item to delete/rate it</i></small>"));

    this->listWatchlist = new QListWidget();
    this->btnOpenFile = new QPushButton("Open Watchlist file (CSV / HTML)");

    rightLayout->addWidget(this->listWatchlist);
    rightLayout->addWidget(this->btnOpenFile);

    mainLayout->addLayout(leftLayout, 3);
    mainLayout->addLayout(rightLayout, 2);
}

void UserGUI::connectSignals()
{
    QObject::connect(this->btnFilter, &QPushButton::clicked, this, &UserGUI::filterMovies);
    QObject::connect(this->btnNext, &QPushButton::clicked, this, &UserGUI::nextMovie);
    QObject::connect(this->btnAddWatchlist, &QPushButton::clicked, this, &UserGUI::addToWatchlist);
    QObject::connect(this->btnOpenFile, &QPushButton::clicked, this, &UserGUI::openWatchlistFile);
    QObject::connect(this->listWatchlist, &QListWidget::itemDoubleClicked, this, &UserGUI::handleWatchlistRemove);
}

void UserGUI::populateWatchlist()
{
    this->listWatchlist->clear();
    const auto& wl = this->ctrl.getWatchList().getWatchList();
    for (const auto& m : wl) {
        QString text = QString::fromStdString(m.getTitle() + " (" + m.getGenre() + ")");
        this->listWatchlist->addItem(text);
    }
}

void UserGUI::displayMovie()
{
    if (this->currentMovies.empty()) {
        this->lblTitle->setText("<b>Title:</b> No movies available.");
        this->lblGenre->setText("<b>Genre:</b> -");
        this->lblYear->setText("<b>Year:</b> -");
        this->lblLikes->setText("<b>Likes:</b> -");
        return;
    }

    Movie m = this->currentMovies[this->currentIndex];
    this->lblTitle->setText(QString::fromStdString("<b>Title:</b> " + m.getTitle()));
    this->lblGenre->setText(QString::fromStdString("<b>Genre:</b> " + m.getGenre()));
    this->lblYear->setText(QString::fromStdString("<b>Year of release:</b> " + std::to_string(m.getYear())));
    this->lblLikes->setText(QString::fromStdString("<b>Number of likes:</b> " + std::to_string(m.getLikes())));

    QDesktopServices::openUrl(QUrl(QString::fromStdString(m.getTrailer())));
}

void UserGUI::filterMovies()
{
    std::string targetGenre = this->editGenreFilter->text().toStdString();
    this->currentMovies = this->ctrl.filterGenre(targetGenre);
    this->currentIndex = 0;

    if (this->currentMovies.empty()) {
        QMessageBox::information(this, "Info", "No movies found for this genre.");
    }

    this->displayMovie();
}

void UserGUI::nextMovie()
{
    if (this->currentMovies.empty()) return;

    this->currentIndex++;
    if (this->currentIndex >= this->currentMovies.size()) {
        this->currentIndex = 0;
    }
    this->displayMovie();
}

void UserGUI::addToWatchlist()
{
    if (this->currentMovies.empty()) return;
    Movie m = this->currentMovies[this->currentIndex];

    try {
        this->ctrl.addMovieToWatchList(m);
        this->populateWatchlist();
        this->nextMovie();
    }
    catch (std::exception& e) {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
    }
}

void UserGUI::handleWatchlistRemove(QListWidgetItem* item)
{
    int index = this->listWatchlist->row(item);

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Rate Movie", "Did you like this movie? (Will increase likes by 1)",
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    int review = 0;
    if (reply == QMessageBox::Yes) {
        review = 1;
    }
    else if (reply == QMessageBox::Cancel) {
        return;
    }

    try {
        this->ctrl.removeWatchListItem(index, review);
        this->populateWatchlist();

        if (!this->currentMovies.empty()) {
            std::string currentGenre = this->editGenreFilter->text().toStdString();
            this->currentMovies = this->ctrl.filterGenre(currentGenre);

            // Adjust index if necessary (in case movies were removed from DB entirely)
            if (this->currentIndex >= this->currentMovies.size()) {
                this->currentIndex = 0;
            }

            // Update labels without reopening the trailer URL
            if (!this->currentMovies.empty()) {
                Movie m = this->currentMovies[this->currentIndex];
                this->lblLikes->setText(QString::fromStdString("<b>Number of likes:</b> " + std::to_string(m.getLikes())));
            }
        }
    }
    catch (std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void UserGUI::syncData() {
    this->populateWatchlist();

    std::string targetGenre = this->editGenreFilter->text().toStdString();
    this->currentMovies = this->ctrl.filterGenre(targetGenre);

    if (this->currentMovies.empty()) {
        this->lblTitle->setText("<b>Title:</b> No movies available.");
        this->lblGenre->setText("<b>Genre:</b> -");
        this->lblYear->setText("<b>Year:</b> -");
        this->lblLikes->setText("<b>Likes:</b> -");
    }
    else {
        // Prevent crashes if the current movie was deleted from Admin mode
        if (this->currentIndex >= this->currentMovies.size()) {
            this->currentIndex = 0;
        }

        Movie m = this->currentMovies[this->currentIndex];
        this->lblTitle->setText(QString::fromStdString("<b>Title:</b> " + m.getTitle()));
        this->lblGenre->setText(QString::fromStdString("<b>Genre:</b> " + m.getGenre()));
        this->lblYear->setText(QString::fromStdString("<b>Year of release:</b> " + std::to_string(m.getYear())));
        this->lblLikes->setText(QString::fromStdString("<b>Number of likes:</b> " + std::to_string(m.getLikes())));
    }
}

void UserGUI::openWatchlistFile()
{
    this->ctrl.openWatchlistFile();
}
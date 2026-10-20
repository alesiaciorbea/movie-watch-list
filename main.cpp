#include <QtWidgets/QApplication>
#include "StartGUI.h"
#include "MainMenuGUI.h"
#include "Controller.h"
#include "Repository.h"
#include "SqliteRepository.h"
#include "WatchList.h"
#include "CSVWatchlist.h"
#include "HTMLWatchlist.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    StartGUI* startWindow = new StartGUI();
    startWindow->show();

    // Declare backend pointers here so they live throughout the application's lifetime
    Repository* repo = nullptr;
    FileWatchlist* fileWatchlist = nullptr;
    WatchList* watchList = nullptr;
    Controller* ctrl = nullptr;
    MainMenuGUI* mainMenu = nullptr;


    QObject::connect(startWindow, &StartGUI::startApplication, [&]() {

        if (startWindow->isSQLiteSelected()) {
            repo = new SqliteRepository("movies.db");
        }
        else {
            repo = new Repository("movies.txt");
        }

        if (startWindow->isCSVSelected()) {
            fileWatchlist = new CSVWatchlist("watchlist.csv");
        }
        else {
            fileWatchlist = new HTMLWatchlist("watchlist.html");
        }

        watchList = new WatchList(fileWatchlist);

        ctrl = new Controller(*repo, *watchList);
        mainMenu = new MainMenuGUI(*ctrl);

        mainMenu->show();

        startWindow->close();
        startWindow->deleteLater();
        });

    return a.exec();
}
#include "MainMenuGUI.h"

MainMenuGUI::MainMenuGUI(Controller& controller, QWidget* parent)
    : QWidget(parent), ctrl(controller) {

    this->setWindowTitle("Movie Manager - Main Menu");
    this->resize(400, 250);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* titleLabel = new QLabel("<h2>MOVIE MANAGER</h2>");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    this->btnAdmin = new QPushButton("1. Administrator Mode");
    this->btnUser = new QPushButton("2. User Mode");
    this->btnChart = new QPushButton("3. View Statistics (Bonus)");
    this->btnWatchListTable = new QPushButton("4. Open Watchlist Table");

    mainLayout->addWidget(this->btnAdmin);
    mainLayout->addWidget(this->btnUser);
    mainLayout->addWidget(this->btnChart);
    mainLayout->addWidget(this->btnWatchListTable);
    mainLayout->addStretch();


    this->adminWindow = nullptr;
    this->userWindow = nullptr;
    this->chartWindow = nullptr;

    this->watchListTableWindow = nullptr;

    QObject::connect(this->btnAdmin, &QPushButton::clicked, this, &MainMenuGUI::openAdminMode);
    QObject::connect(this->btnUser, &QPushButton::clicked, this, &MainMenuGUI::openUserMode);
    QObject::connect(this->btnChart, &QPushButton::clicked, this, &MainMenuGUI::openChartMode);
    QObject::connect(this->btnWatchListTable, &QPushButton::clicked, this, [this]() {
        if (this->watchListTableWindow == nullptr) {
            this->watchListTableWindow = new WatchListWindow(this->ctrl.getWatchList());
        }

        this->watchListTableWindow->refreshTable();
        this->watchListTableWindow->show();
        });
}

void MainMenuGUI::openAdminMode() {
    if (this->adminWindow == nullptr) {
        this->adminWindow = new AdminGUI(this->ctrl);
    }

    this->adminWindow->populateList();
    this->adminWindow->show();
}

void MainMenuGUI::openUserMode() {
    if (this->userWindow == nullptr) {
        this->userWindow = new UserGUI(this->ctrl);
    }

    this->userWindow->syncData();
    this->userWindow->show();
}

void MainMenuGUI::openChartMode() {
    if (this->chartWindow == nullptr) {
        this->chartWindow = new ChartGUI(this->ctrl);
    }

    this->chartWindow->update();
    this->chartWindow->show();
}
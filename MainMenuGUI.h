#pragma once
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "AdminGUI.h"
#include "UserGUI.h"
#include "Controller.h"
#include "ChartGUI.h"
#include "WatchListWindow.h"

class MainMenuGUI : public QWidget {
    Q_OBJECT
public:
    MainMenuGUI(Controller& controller, QWidget* parent = nullptr);

private:
    Controller& ctrl;
    QPushButton* btnAdmin;
    QPushButton* btnUser;

    QPushButton* btnChart;
    ChartGUI* chartWindow;

    QPushButton* btnWatchListTable;
    WatchListWindow* watchListTableWindow;

    AdminGUI* adminWindow;
    UserGUI* userWindow;

private slots:
    void openAdminMode();
    void openUserMode();
    void openChartMode();
};
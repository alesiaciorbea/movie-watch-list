#pragma once
#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>
#include <QHeaderView>
#include "WatchListTableModel.h"

class WatchListWindow : public QWidget {
    Q_OBJECT
private:
    QTableView* tableView;
    WatchListTableModel* tableModel;

public:
    WatchListWindow(WatchList& watchList, QWidget* parent = nullptr);
    void refreshTable();
};
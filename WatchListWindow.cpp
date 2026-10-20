#include "WatchListWindow.h"

WatchListWindow::WatchListWindow(WatchList& watchList, QWidget* parent) : QWidget(parent) {
    this->setWindowTitle("My Watchlist - Table View");
    this->resize(600, 300);

    QVBoxLayout* layout = new QVBoxLayout(this);
    this->tableView = new QTableView();

    this->tableModel = new WatchListTableModel(watchList);

    this->tableView->setModel(this->tableModel);

    this->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    layout->addWidget(this->tableView);
}

void WatchListWindow::refreshTable() {
    this->tableModel->refresh();
}
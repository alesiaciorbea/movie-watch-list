#include "WatchListTableModel.h"

WatchListTableModel::WatchListTableModel(WatchList& watchList, QObject* parent)
    : QAbstractTableModel(parent), watchList(watchList) {
}

int WatchListTableModel::rowCount(const QModelIndex& parent) const {
    return this->watchList.getWatchList().size();
}

int WatchListTableModel::columnCount(const QModelIndex& parent) const {
    return 4;
}

QVariant WatchListTableModel::data(const QModelIndex& index, int role) const {
    int row = index.row();
    int column = index.column();

    if (!index.isValid() || row >= this->watchList.getWatchList().size()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        const auto& movie = this->watchList.getWatchList()[row];

        switch (column) {
        case 0: return QString::fromStdString(movie.getTitle());
        case 1: return QString::fromStdString(movie.getGenre());
        case 2: return movie.getYear();
        case 3: return movie.getLikes();
        default: return QVariant();
        }
    }
    return QVariant();
}

QVariant WatchListTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return QString("Title");
        case 1: return QString("Genre");
        case 2: return QString("Year");
        case 3: return QString("Likes");
        default: return QVariant();
        }
    }
    return QVariant();
}

void WatchListTableModel::refresh() {
    emit layoutAboutToBeChanged();
    emit layoutChanged();
}
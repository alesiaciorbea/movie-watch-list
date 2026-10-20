#include "AdminGUI.h"
#include <exception>
#include <stdexcept>
#include <QStringList>

AdminGUI::AdminGUI(Controller& controller, QWidget* parent)
    : QWidget(parent), ctrl(controller) {
    this->initGUI();
    this->populateList();
    this->connectSignals();
}

void AdminGUI::initGUI() {
    this->setWindowTitle("Administrator Mode");
    this->resize(900, 500);

    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    this->movieList = new QListWidget();
    mainLayout->addWidget(this->movieList);

    QVBoxLayout* rightLayout = new QVBoxLayout();
    QFormLayout* formLayout = new QFormLayout();

    this->editTitle = new QLineEdit();
    this->editGenre = new QLineEdit();
    this->editYear = new QLineEdit();
    this->editLikes = new QLineEdit();
    this->editTrailer = new QLineEdit();

    formLayout->addRow("Title:", this->editTitle);
    formLayout->addRow("Genre:", this->editGenre);
    formLayout->addRow("Year:", this->editYear);
    formLayout->addRow("Likes:", this->editLikes);
    formLayout->addRow("Trailer Link:", this->editTrailer);
    rightLayout->addLayout(formLayout);

    QHBoxLayout* crudButtons = new QHBoxLayout();
    this->btnAdd = new QPushButton("Add");
    this->btnRemove = new QPushButton("Remove");
    this->btnUpdate = new QPushButton("Update");
    crudButtons->addWidget(this->btnAdd);
    crudButtons->addWidget(this->btnRemove);
    crudButtons->addWidget(this->btnUpdate);
    rightLayout->addLayout(crudButtons);

    QHBoxLayout* historyButtons = new QHBoxLayout();
    this->btnUndo = new QPushButton("Undo");
    this->btnRedo = new QPushButton("Redo");
    historyButtons->addWidget(this->btnUndo);
    historyButtons->addWidget(this->btnRedo);
    rightLayout->addLayout(historyButtons);

    mainLayout->addLayout(rightLayout);
}

void AdminGUI::connectSignals() {
    QObject::connect(this->btnAdd, &QPushButton::clicked, this, &AdminGUI::addMovie);
    QObject::connect(this->btnRemove, &QPushButton::clicked, this, &AdminGUI::removeMovie);
    QObject::connect(this->btnUpdate, &QPushButton::clicked, this, &AdminGUI::updateMovie);

    QObject::connect(this->btnUndo, &QPushButton::clicked, this, &AdminGUI::undoAction);
    QObject::connect(this->btnRedo, &QPushButton::clicked, this, &AdminGUI::redoAction);

    QObject::connect(this->movieList, &QListWidget::itemSelectionChanged, this, &AdminGUI::populateForm);

    QShortcut* shortcutUndo = new QShortcut(QKeySequence("Ctrl+Z"), this);
    QObject::connect(shortcutUndo, &QShortcut::activated, this, &AdminGUI::undoAction);

    QShortcut* shortcutRedo = new QShortcut(QKeySequence("Ctrl+Y"), this);
    QObject::connect(shortcutRedo, &QShortcut::activated, this, &AdminGUI::redoAction);
}

void AdminGUI::undoAction() {
    try {
        this->ctrl.undo();
        this->populateList();
    }
    catch (std::exception& e) {
        QMessageBox::warning(this, "Undo", e.what());
    }
}

void AdminGUI::redoAction() {
    try {
        this->ctrl.redo();
        this->populateList();
    }
    catch (std::exception& e) {
        QMessageBox::warning(this, "Redo", e.what());
    }
}

void AdminGUI::populateList() {
    this->movieList->clear();
    for (const auto& m : this->ctrl.getRepo().getMovies()) {
        std::string info = m.getTitle() + " | " +
            m.getGenre() + " | " +
            std::to_string(m.getYear()) + " | " +
            std::to_string(m.getLikes()) + " likes";

        this->movieList->addItem(QString::fromStdString(info));
    }
}

void AdminGUI::populateForm() {
    if (this->movieList->selectedItems().isEmpty()) return;
    QString selectedText = this->movieList->selectedItems().first()->text();
    std::string title = selectedText.split(" | ")[0].toStdString();

    for (const auto& m : this->ctrl.getRepo().getMovies()) {
        if (m.getTitle() == title) {
            this->editTitle->setText(QString::fromStdString(m.getTitle()));
            this->editGenre->setText(QString::fromStdString(m.getGenre()));
            this->editYear->setText(QString::number(m.getYear()));
            this->editLikes->setText(QString::number(m.getLikes()));
            this->editTrailer->setText(QString::fromStdString(m.getTrailer()));
            break;
        }
    }
}

void AdminGUI::addMovie() {
    try {
        std::string title = this->editTitle->text().toStdString();
        std::string genre = this->editGenre->text().toStdString();

        int year = this->editYear->text().toInt();
        int likes = this->editLikes->text().toInt();

        std::string trailer = this->editTrailer->text().toStdString();

        this->ctrl.addMovie(title, genre, year, likes, trailer);

        this->populateList();

        this->editTitle->clear();
        this->editGenre->clear();
        this->editYear->clear();
        this->editLikes->clear();
        this->editTrailer->clear();

    }
    catch (std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void AdminGUI::removeMovie() {
    try {
        std::string title = this->editTitle->text().toStdString();

        this->ctrl.removeMovie(title);

        this->populateList();

        this->editTitle->clear();
        this->editGenre->clear();
        this->editYear->clear();
        this->editLikes->clear();
        this->editTrailer->clear();

    }
    catch (std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void AdminGUI::updateMovie() {
    try {
        // The title acts as the unique identifier and cannot be changed here
        std::string title = this->editTitle->text().toStdString();

        std::string genre = this->editGenre->text().toStdString();
        int year = this->editYear->text().toInt();
        int likes = this->editLikes->text().toInt();
        std::string trailer = this->editTrailer->text().toStdString();

        this->ctrl.updateMovie(title, genre, year, likes, trailer);

        this->populateList();

    }
    catch (std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}
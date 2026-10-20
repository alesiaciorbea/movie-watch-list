#pragma once
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QShortcut>
#include "Controller.h"

class AdminGUI : public QWidget {
    Q_OBJECT
public:
    AdminGUI(Controller& controller, QWidget* parent = nullptr);
    void populateList(); // Public so MainMenu can refresh it

private:
    Controller& ctrl;

    QListWidget* movieList;
    QLineEdit* editTitle;
    QLineEdit* editGenre;
    QLineEdit* editYear;
    QLineEdit* editLikes;
    QLineEdit* editTrailer;

    QPushButton* btnAdd;
    QPushButton* btnRemove;
    QPushButton* btnUpdate;
    QPushButton* btnUndo;
    QPushButton* btnRedo;

    void initGUI();
    void connectSignals();

private slots:
    void addMovie();
    void removeMovie();
    void updateMovie();
    void undoAction();
    void redoAction();
    void populateForm();
};
#include "StartGUI.h"
#include <QButtonGroup>

StartGUI::StartGUI(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    mainLayout->addWidget(new QLabel("<b>What database system do you want to use?</b>"));
    this->radioText = new QRadioButton("Text File (movies.txt)");
    this->radioSQLite = new QRadioButton("SQLite Database (movies.db)");
    this->radioText->setChecked(true);
    mainLayout->addWidget(this->radioText);
    mainLayout->addWidget(this->radioSQLite);

    // Group the database radio buttons so they act as a separate unit
    QButtonGroup* dbGroup = new QButtonGroup(this);
    dbGroup->addButton(this->radioText);
    dbGroup->addButton(this->radioSQLite);

    mainLayout->addWidget(new QLabel("<b>What format do you want for the Watchlist?</b>"));
    this->radioCSV = new QRadioButton("CSV");
    this->radioHTML = new QRadioButton("HTML");
    this->radioCSV->setChecked(true);
    mainLayout->addWidget(this->radioCSV);
    mainLayout->addWidget(this->radioHTML);

    // Group the format radio buttons so they act as a separate unit
    QButtonGroup* formatGroup = new QButtonGroup(this);
    formatGroup->addButton(this->radioCSV);
    formatGroup->addButton(this->radioHTML);

    this->btnStart = new QPushButton("Start Application");
    mainLayout->addWidget(this->btnStart);

    QObject::connect(this->btnStart, &QPushButton::clicked, this, &StartGUI::startApplication);
}

bool StartGUI::isSQLiteSelected() const {
    return this->radioSQLite->isChecked();
}

bool StartGUI::isCSVSelected() const {
    return this->radioCSV->isChecked();
}